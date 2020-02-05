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

#ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_SIMPLECONTROLLER_H
#define __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_SIMPLECONTROLLER_H

#include "inet/common/INETDefs.h"
#include "inet/common/lifecycle/ILifecycle.h"
//#include "inet/common/lifecycle/ModuleOperations.h"
//#include "inet/common/packet/Packet.h"
//#include "inet/linklayer/ethernet/EtherFrame_m.h"
//#include "inet/networklayer/contract/IInterfaceTable.h"

namespace shortestPathLoad {
using namespace inet;

class RoutingUnit : public cSimpleModule//: public OperationalBase
{
protected:

    virtual void initialize(int stage) override;

};

} // namespace shortestPathLoad

#endif // ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_SIMPLECONTROLLER_H

