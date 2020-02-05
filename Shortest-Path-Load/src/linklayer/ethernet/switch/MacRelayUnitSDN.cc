// Copyright (C) 2013 OpenSim Ltd.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//


#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Protocol.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/StringFormat.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/linklayer/ethernet/EtherMacBase.h"
#include "inet/linklayer/ethernet/Ethernet.h"
//EXTRA BEGIN
//#include "inet/linklayer/ethernet/switch/MacRelayUnit.h"
#include "src/linklayer/ethernet/switch/MacRelayUnitSDN.h"
#include "src/common/Simsignals.h"

//namespace inet {
namespace shortestPathLoad {
//EXTRA END

Define_Module(MacRelayUnitSDN);


void MacRelayUnitSDN::initialize(int stage)
{
    LayeredProtocolBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numProcessedFrames = numDiscardedFrames = 0;

        macTable = getModuleFromPar<IMacAddressTable>(par("macTableModule"), this);
        ifTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);

        WATCH(numProcessedFrames);
        WATCH(numDiscardedFrames);
    }
    else if (stage == INITSTAGE_LINK_LAYER) {
        registerService(Protocol::ethernetMac, nullptr, gate("ifIn"));
        registerProtocol(Protocol::ethernetMac, gate("ifOut"), nullptr);
    }
}

//EXTRA BEGIN
void MacRelayUnitSDN::handleMessageWhenUp(cMessage *message)
{
    if (message->isSelfMessage())
        handleSelfMessage(message);
    else if (isUpperMessage(message))
        handleUpperMessage(message);
    else if (isLowerMessage(message))
        handleLowerMessage(message);
    else if (isControlerMessage(message))
        handleControllerMessage(message);
    else
        throw cRuntimeError("Message '%s' received on unexpected gate '%s'", message->getName(), message->getArrivalGate()->getFullName());
}

void MacRelayUnitSDN::handleControllerMessage(cMessage *message)
{
    if (!message->isPacket())
        handleControllerCommand(message);
    else {
        emit(packetReceivedFromControllerSignal, message);
        handleControllerPacket(check_and_cast<Packet *>(message));
    }
}

void MacRelayUnitSDN::handleControllerCommand(cMessage *message)
{
    throw cRuntimeError("Controller command '%s' is not handled.", message->getName());
}

void MacRelayUnitSDN::handleControllerPacket(Packet *packet)
{
    throw cRuntimeError("Upper packet '%s' is not handled.", packet->getName());
}
//EXTRA END

void MacRelayUnitSDN::handleLowerPacket(Packet *packet)
{
    handleAndDispatchFrame(packet);
    updateDisplayString();
}

void MacRelayUnitSDN::updateDisplayString() const
{
    auto text = StringFormat::formatString(par("displayStringTextFormat"), [&] (char directive) {
        static std::string result;
        switch (directive) {
            case 'p':
                result = std::to_string(numProcessedFrames);
                break;
            case 'd':
                result = std::to_string(numDiscardedFrames);
                break;
            default:
                throw cRuntimeError("Unknown directive: %c", directive);
        }
        return result.c_str();
    });
    getDisplayString().setTagArg("t", 0, text);
}

void MacRelayUnitSDN::broadcast(Packet *packet, int arrivalInterfaceId)
{
    EV_DETAIL << "Broadcast frame " << packet << endl;

    auto oldPacketProtocolTag = packet->removeTag<PacketProtocolTag>();
    packet->clearTags();
    auto newPacketProtocolTag = packet->addTag<PacketProtocolTag>();
    *newPacketProtocolTag = *oldPacketProtocolTag;
    delete oldPacketProtocolTag;
    packet->trim();

    int numPorts = ifTable->getNumInterfaces();
    for (int i = 0; i < numPorts; i++) {
        InterfaceEntry *ie = ifTable->getInterface(i);
        if (ie->isLoopback() || !ie->isBroadcast())
            continue;
        int ifId = ie->getInterfaceId();
        if (arrivalInterfaceId != ifId) {
            Packet *dupFrame = packet->dup();
            dupFrame->addTagIfAbsent<InterfaceReq>()->setInterfaceId(ifId);
            emit(packetSentToLowerSignal, dupFrame);
            send(dupFrame, "ifOut");
        }
    }
    delete packet;
}

void MacRelayUnitSDN::handleAndDispatchFrame(Packet *packet)
{
    //FIXME : should handle multicast mac addresses correctly

    const auto& frame = packet->peekAtFront<EthernetMacHeader>();
    int arrivalInterfaceId = packet->getTag<InterfaceInd>()->getInterfaceId();

    numProcessedFrames++;

    // update address table
    learn(frame->getSrc(), arrivalInterfaceId);

    // handle broadcast frames first
    if (frame->getDest().isBroadcast()) {
        EV << "Broadcasting broadcast frame " << frame << endl;
        broadcast(packet, arrivalInterfaceId);
        return;
    }

    // Finds output port of destination address and sends to output port
    // if not found then broadcasts to all other ports instead
    int outputInterfaceId = macTable->getInterfaceIdForAddress(frame->getDest());
    // should not send out the same frame on the same ethernet port
    // (although wireless ports are ok to receive the same message)
    if (arrivalInterfaceId == outputInterfaceId) {
        EV << "Output port is same as input port, " << packet->getFullName()
           << " dest " << frame->getDest() << ", discarding frame\n";
        numDiscardedFrames++;
        delete packet;
        return;
    }

    if (outputInterfaceId >= 0) {
        EV << "Sending frame " << frame << " with dest address " << frame->getDest() << " to port " << outputInterfaceId << endl;
        auto oldPacketProtocolTag = packet->removeTag<PacketProtocolTag>();
        packet->clearTags();
        auto newPacketProtocolTag = packet->addTag<PacketProtocolTag>();
        *newPacketProtocolTag = *oldPacketProtocolTag;
        delete oldPacketProtocolTag;
        packet->addTag<InterfaceReq>()->setInterfaceId(outputInterfaceId);
        packet->trim();
        emit(packetSentToLowerSignal, packet);
        send(packet, "ifOut");
    }
    else {
        EV << "Dest address " << frame->getDest() << " unknown, broadcasting frame " << packet << endl;
        broadcast(packet, arrivalInterfaceId);
    }
}

void MacRelayUnitSDN::start()
{
}

void MacRelayUnitSDN::stop()
{
}

void MacRelayUnitSDN::learn(MacAddress srcAddr, int arrivalInterfaceId)
{
    macTable->updateTableWithAddress(arrivalInterfaceId, srcAddr);
}

void MacRelayUnitSDN::finish()
{
    recordScalar("processed frames", numProcessedFrames);
    recordScalar("discarded frames", numDiscardedFrames);
}

} // namespace shortestPathLoad

