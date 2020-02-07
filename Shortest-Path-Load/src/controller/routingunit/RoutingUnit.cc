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

#include "src/controller/routingunit/RoutingUnit.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
//#include "inet/common/packet/Packet.h"

namespace shortestPathLoad {

Define_Module(RoutingUnit);

RoutingUnit::~RoutingUnit()
{
}

void RoutingUnit::initialize(int stage)
{
    RoutingUnitBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
            //throw cRuntimeError("Invalid startTime/stopTime parameters");
    }
}

void RoutingUnit::handleStartOperation(LifecycleOperation *operation)
{

}

void RoutingUnit::handleStopOperation(LifecycleOperation *operation)
{
}

void RoutingUnit::handleCrashOperation(LifecycleOperation *operation)
{
}


} // namespace shortestPathLoad

