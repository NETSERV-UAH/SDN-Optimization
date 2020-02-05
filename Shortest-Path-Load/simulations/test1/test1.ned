// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//


package shortestPathLoad.simulations.test1;

//import inet.linklayer.ethernet.EtherBus;
//import inet.linklayer.ethernet.EtherHub;
//import inet.node.ethernet.EtherHost;
import inet.node.inet.StandardHost;
import shortestPathLoad.src.node.ethernet.EtherSwitchSDN;
import shortestPathLoad.src.node.controller.SimpleController;
import ned.DatarateChannel;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.linklayer.configurator.L2NetworkConfigurator;
import inet.common.scenario.ScenarioManager;
import inet.common.misc.ThruputMeteringChannel;


//
// A 100Mb/s Ethernet cable.
//
channel cable extends ThruputMeteringChannel
{
    parameters:
        delay = 0.1us;
        datarate = 100Mbps;
        thruputDisplayFormat = "b B U";
}


network test1
{
    parameters:
        @display("i=old/cloud");

    submodules:

        client1: StandardHost {
            @display("p=53.64,322.9575,row,150;i=device/laptop");
            gates:

                ethg[1];

        }
        client2: StandardHost {
            @display("p=53.64,219.03,row,150;i=device/pc");
            gates:

                ethg[1];

        }
        client3: StandardHost {
            @display("p=53.64,128.5125,row,150;i=device/pc");
            gates:
                ethg[1];
        }
        client4: StandardHost {
            @display("p=164.27249,31.289999,row,150;i=device/pc");
            gates:

                ethg[1];

        }
        client5: StandardHost {
            @display("p=328.54498,25.7025,row,150;i=device/pc");
            gates:
                ethg[1];


        }
        client6: StandardHost {
            @display("p=472.70248,31.289999,row,150;i=device/pc");
            gates:

                ethg[1];

        }
        server1: StandardHost {
            @display("p=745.3725,219.03,row,150;i=device/server_l");
            gates:

                ethg[1];


        }
        server2: StandardHost {
            @display("p=628.035,40.23,row,150;i=device/server_l");
            gates:

                ethg[1];


        }

        switchA: EtherSwitchSDN {
            parameters:
                @display("p=184.3875,217.91249");
            gates:
                ethg[5];
        }
        switchB: EtherSwitchSDN {
            parameters:
                @display("p=328.54498,127.395");
            gates:
                ethg[5];
        }
        switchC: EtherSwitchSDN {
            parameters:
                @display("p=328.54498,302.8425");
            gates:
                ethg[2];
        }
        switchD: EtherSwitchSDN {
            parameters:
                @display("p=472.70248,217.91249");
            gates:
                ethg[4];
        }
        switchE: EtherSwitchSDN {
            parameters:
                @display("p=628.035,217.91249");
            gates:
                ethg[2];
        }

        controller: SimpleController {
            @display("p=511,303");
            gates:
                southBoundInterfaces[5];
        }

        configurator: Ipv4NetworkConfigurator {
            @display("p=328,406");
        }

        l2NetworkConfigurator: L2NetworkConfigurator {
            @display("p=184,406");
        }

        scenarioManager: ScenarioManager {
            @display("p=53,406");
        }


    connections:

        switchA.ethg++ <--> cable <--> switchB.ethg++;
        switchC.ethg++ <--> cable <--> switchD.ethg++;
        switchE.ethg++ <--> cable <--> server1.ethg++;
        switchC.ethg++ <--> cable <--> switchA.ethg++;
        switchB.ethg++ <--> cable <--> switchD.ethg++;
        switchD.ethg++ <--> cable <--> switchE.ethg++;
        client3.ethg++ <--> cable <--> switchA.ethg++;
        client2.ethg++ <--> cable <--> switchA.ethg++;
        client1.ethg++ <--> cable <--> switchA.ethg++;
        client4.ethg++ <--> cable <--> switchB.ethg++;
        client5.ethg++ <--> cable <--> switchB.ethg++;
        client6.ethg++ <--> cable <--> switchB.ethg++;
        server2.ethg++ <--> cable <--> switchD.ethg++;

        controller.southBoundInterfaces++ <--> switchD.controllerGate;
        controller.southBoundInterfaces++ <--> switchC.controllerGate;
        controller.southBoundInterfaces++ <--> switchB.controllerGate;
        controller.southBoundInterfaces++ <--> switchA.controllerGate;
        controller.southBoundInterfaces++ <--> switchE.controllerGate;
}
