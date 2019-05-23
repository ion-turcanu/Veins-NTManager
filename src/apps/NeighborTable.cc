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

#include "NeighborTable.h"

NeighborTable::NeighborTable(int myID) {
    this->myID = myID;
    myPosition = veins::Coord(0,0,0);
    mySpeed = veins::Coord(0,0,0);
}

NeighborTable::~NeighborTable() {
}


int NeighborTable::processEntry(NeighborTable_Neighbor entry) {
    int ret_val = -1;
    NeighborTable_t::iterator it_neighbors = neighbors.find(entry.id);
    if(it_neighbors == neighbors.end()) {
        //new entry
        entry.last_seen = simTime();
        neighbors.insert(std::make_pair(entry.id, entry));
        ret_val = 1;
    } else {
        //updating entry
        NeighborTable_Neighbor& existing_entry = it_neighbors->second;
        existing_entry.update(entry);
        ret_val = 2;
    }

    return ret_val;
}


int NeighborTable::expireEntries(simtime_t time) {
    int expired_neighbors = 0;
    NeighborTable_t::iterator it_neighbors = neighbors.begin();
    while(it_neighbors != neighbors.end()) {
        simtime_t last_seen = it_neighbors->second.last_seen;
        if(last_seen < simTime() - time) {
            neighbors.erase(it_neighbors++);
            expired_neighbors++;
        } else {
            it_neighbors++;
        }
    }
    return expired_neighbors;
}


std::map<int, NeighborTable::NeighborTable_Neighbor> NeighborTable::getNeighborTable() {
    std::map<int, NeighborTable::NeighborTable_Neighbor> resultMap;
    NeighborTable_t::iterator it_neighbors;
    for(it_neighbors = neighbors.begin(); it_neighbors != neighbors.end(); it_neighbors++) {
        resultMap.insert(std::make_pair(it_neighbors->first, it_neighbors->second));
    }
    return resultMap;
}

