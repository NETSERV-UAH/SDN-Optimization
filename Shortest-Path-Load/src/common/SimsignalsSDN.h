//
// Copyright (C) 2005 Andras Varga
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

#ifndef __SHORTESTPATHLOAD_SRC_COMMON_SIMSIGNALS_H
#define __SHORTESTPATHLOAD_SRC_COMMON_SIMSIGNALS_H

#include "inet/common/INETDefs.h"
#include "inet/common/Simsignals_m.h"



namespace shortestPathLoad {
using namespace inet;


/**
 * Signals for publish/subscribe mechanisms.
 */
// TODO document associated signals detail structs
extern simsignal_t
// - layer 2 (data-link)
//...

// - layer 3 (network)
//...

// layer 3 - Routing Table
//...

// layer 3 - Ipv4
//...

// for PIM
//...

// layer 3 - Ipv6
//...

//layer 3 - ISIS
//...

// - layer 4 (transport)
//...

// - layer 7 (application)
//...

// general
    packetReceivedFromControllerSignal,
    packetSentToControllerSignal;
    //EXTRA END

/**
 * Utility function
 */
//...
} // namespace shortestPathLoad

#endif // ifndef __SHORTESTPATHLOAD_SRC_COMMON_SIMSIGNALS_H

