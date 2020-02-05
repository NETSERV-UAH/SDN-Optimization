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


simple RoutingUnit 
{
    parameters:
        @display("i=block/control;bgb=201,133");
        @class(shortestPathLoad::RoutingUnit);
        int numSouthBoundInterfaces = default(0);  // minimum number of switch interfaces
        bool hasTable = default(true);
        string table = default("table1");
        //table.agingtime = default(120s);

    gates:
        input ifIn[];
        output ifOut[];

}

