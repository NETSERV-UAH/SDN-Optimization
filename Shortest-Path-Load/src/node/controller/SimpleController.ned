//
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

package shortestPathLoad.src.node.controller;

//import table;
import inet.common.lifecycle.NodeStatus;
import inet.common.MessageDispatcher;
import shortestPathLoad.src.controller.routingunit.RoutingUnit;
//
module SimpleController
{
    parameters:
        @networkNode();
        @labels(node,controller-node);
        @display("i=block/control;bgb=201,133");
        bool hasStatus = default(false);
        bool hasTable = default(true);
        string table = default("table1");
        //table.agingtime = default(120s);


    gates:
        inout southBoundInterfaces[];

    submodules:
        routingUnit: RoutingUnit {
            parameters:
                @display("p=56.033333,47.149998;is=m");
            gates:
                ifIn[sizeof(southBoundInterfaces)];
                ifOut[sizeof(southBoundInterfaces)];
        }

        //North Bound
//        up: MessageDispatcher {
//            parameters:
//                @display("p=800,160;b=1200,5");
//        }

		//South Bound
//		down: MessageDispatcher {
//            parameters:
//                @display("p=800,380;b=1200,5");
//        }

//        status: NodeStatus if hasStatus {
//            @display("p=66,54;is=s");
//        }
//        table: Table if hasTable {
//            @display("p=100,400;is=s");
//        }

    connections:
        //Since the simple controller has not any interfaces,
        //the soutbound interfaces are directly connected to the routing unit. 
        for i=0..sizeof(southBoundInterfaces)-1 {
            southBoundInterfaces$i[i] --> { @display("m=s"); } --> routingUnit.ifIn++;
            southBoundInterfaces$o[i] <-- { @display("m=s"); } <-- routingUnit.ifOut++;
        }
}

