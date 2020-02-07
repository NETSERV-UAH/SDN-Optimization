// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "src/controller/routingunit/base/RoutingUnitBase.h"

namespace shortestPathLoad {

simsignal_t RoutingUnitBase::xSignal = registerSignal("xNedSignal");

void RoutingUnitBase::initialize(int stage)
{
    ControllerBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        packetsSent = packetsRcvd = 0;

        WATCH(packetsSent);
        WATCH(packetsRcvd);
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
    }
}

void RoutingUnitBase::handleMessageWhenUp(cMessage *msg)
{
    if (msg->isSelfMessage())
        handleTimer(msg);
    //else

}

void RoutingUnitBase::sendPacket(Packet *msg)
{
    emit(xSignal, msg);

    packetsSent++;
}

void RoutingUnitBase::refreshDisplay() const
{
    ControllerBase::refreshDisplay();
    getDisplayString().setTagArg("t", 0, "state");
}

void RoutingUnitBase::finish()
{
    std::string modulePath = getFullPath();

    EV_INFO << modulePath << ": sent " << packetsSent << " packets\n";
    EV_INFO << modulePath << ": received "<< packetsRcvd << " packets\n";
}

} // namespace shortestPathLoad

