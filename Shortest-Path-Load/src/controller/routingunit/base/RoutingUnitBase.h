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

#ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_ROUTINGUNIT_BASE_ROUTINGUNITBASE_H
#define __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_ROUTINGUNIT_BASE_ROUTINGUNITBASE_H

#include "inet/common/INETDefs.h"
#include "src/controller/base/ControllerBase.h"


namespace shortestPathLoad {
using namespace inet;


class RoutingUnitBase : public ControllerBase
{
  protected:
    // statistics
    int packetsSent;
    int packetsRcvd;

    //statistics:
    static simsignal_t xSignal;

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void handleMessageWhenUp(cMessage *msg) override;
    virtual void finish() override;
    virtual void refreshDisplay() const override;

    /* Utility functions */
    virtual void sendPacket(Packet *pkt);

};

} // namespace shortestPathLoad

#endif // ifndef __SHORTESTPATHLOAD_SRC_NODE_CONTROLLER_ROUTINGUNIT_BASE_ROUTINGUNITBASE_H

