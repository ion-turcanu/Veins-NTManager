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

#ifndef APPS_NEIGHBORTABLE_H_
#define APPS_NEIGHBORTABLE_H_

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <omnetpp.h>
#include <vector>
#include "veins/base/utils/Coord.h"


class NeighborTable {

public:

    /** @brief class defining the object Neighbor */
    class NeighborTable_Neighbor {
    public:

        /** @brief constructor */
        NeighborTable_Neighbor() {
            id = -1;
            last_seen = 0;
            position = veins::Coord(0,0,0);
            speed = veins::Coord(0,0,0);
        }

        /** @brief destructor */
        ~NeighborTable_Neighbor() {};

        /** @brief Updates the information related to a neighbor
         *
         *  @param newEntry: neighbor
         */
        void update(NeighborTable_Neighbor newEntry) {
            id = newEntry.id;
            last_seen = simTime();
            position = newEntry.position;
            speed = newEntry.speed;
        }

        int id;                     // neighbor id
        veins::Coord position;      // neighbor position
        veins::Coord speed;         // neighbor speed
        simtime_t last_seen;        // the last time when the neighbor was inserted
    };

    NeighborTable(int myID);
    virtual ~NeighborTable();

    /** @brief Process a new beacon. If this is the first time I receive from this sender, create a new entry, otherwise update existing information.
     *
     *  @param newEntry: neighbor
     *  @return int: =1 for new Entry, =2 updated Entry, -1 for error
     */
    int processEntry(NeighborTable_Neighbor entry);

    /** @brief Deletes expired entries (outdated information)
     *
     *  @param time: the amount of time after which the information is deemed to be outdated
     *  @return int: the number of expired neighbors
     */
    int expireEntries(simtime_t time);

    /** @brief Gets the local neighbor table containing the latest information */
    std::map<int, NeighborTable::NeighborTable_Neighbor> getNeighborTable();


private:
    int myID;
    veins::Coord myPosition;
    veins::Coord mySpeed;
    typedef std::map<int, NeighborTable_Neighbor> NeighborTable_t;
    NeighborTable_t neighbors;

};

#endif /* APPS_NEIGHBORTABLE_H_ */
