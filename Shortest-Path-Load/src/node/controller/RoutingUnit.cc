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


/*#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/LayeredProtocolBase.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/Protocol.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/StringFormat.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/linklayer/ethernet/EtherMacBase.h"
#include "inet/linklayer/ethernet/Ethernet.h"*/
#include "src/node/controller/RoutingUnit.h"

namespace shortestPathLoad {

Define_Module(RoutingUnit);

void RoutingUnit::initialize(int stage)
{
    //cSimpleModule::initialize(stage);
    int test = 0;
    WATCH(test);

}

} // namespace shortestPathLoad
