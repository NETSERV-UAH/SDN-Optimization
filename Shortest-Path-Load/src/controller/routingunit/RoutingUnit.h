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

#ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_ROUTINGUNIT_BASE_ROUTINGUNIT_H
#define __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_ROUTINGUNIT_BASE_ROUTINGUNIT_H

#include "inet/common/INETDefs.h"

#include "src/controller/routingunit/base/RoutingUnitBase.h"
#include "inet/common/lifecycle/ILifecycle.h"
#include "inet/common/lifecycle/NodeStatus.h"

namespace shortestPathLoad {
using namespace inet;


class RoutingUnit : public RoutingUnitBase
{
  protected:

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;

    virtual void handleStartOperation(LifecycleOperation *operation) override;
    virtual void handleStopOperation(LifecycleOperation *operation) override;
    virtual void handleCrashOperation(LifecycleOperation *operation) override;

  public:
    RoutingUnit() {}
    virtual ~RoutingUnit();
};

} // namespace shortestPathLoad

#endif // ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_ROUTINGUNIT_BASE_ROUTINGUNIT_H

