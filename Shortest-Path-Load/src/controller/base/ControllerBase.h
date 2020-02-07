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

#ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_BASE_ROUTINGUNIT_H
#define __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_BASE_ROUTINGUNIT_H

#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/OperationalBase.h"

namespace shortestPathLoad {
using namespace inet;

class ControllerBase : public OperationalBase
{
  public:
    ControllerBase();

  protected:
    virtual bool isInitializeStage(int stage) override { return stage == INITSTAGE_NETWORK_LAYER; }
    virtual bool isModuleStartStage(int stage) override { return stage == ModuleStartOperation::STAGE_NETWORK_LAYER; }
    virtual bool isModuleStopStage(int stage) override { return stage == ModuleStopOperation::STAGE_NETWORK_LAYER; }
};
} // namespace shortestPathLoad

#endif // ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_BASE_ROUTINGUNIT_H

