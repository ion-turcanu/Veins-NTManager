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

#include "NeighborsTableApp.h"

using namespace veins;

Define_Module(veins::NeighborsTableApp);


void NeighborsTableApp::initialize(int stage)
{
    BeaconingApp::initialize(stage);
    if (stage == 0) {
        EV << "Initializing " << par("appName").stringValue() << std::endl;
        ntUpdateFrequency = par("ntUpdateFrequency");
        nt_manager = new NeighborTable(myId);
        sigNeighbors_ = registerSignal("sigNeighbors");
        evt_update_nt = new cMessage("delete old neighbors");
        scheduleAt(simTime() + ntUpdateFrequency, evt_update_nt);
    }
    else if (stage == 1) {
        // Initializing members that require initialized other modules goes here
    }
}


NeighborsTableApp::~NeighborsTableApp()
{
    cancelAndDelete(evt_update_nt);
}


void NeighborsTableApp::finish()
{
    BeaconingApp::finish();
    // statistics recording goes here
}


void NeighborsTableApp::onBSM(BeaconMessage* bsm)
{
    NeighborTable::NeighborTable_Neighbor rcvdEntry = createNewEntry(bsm);
    int n = nt_manager->processEntry(rcvdEntry);
    if (n==-1){
        throw cRuntimeError("Error: the received beacon message has not been processed correctly");
    }
    else if (n==1){
        EV << "Inserted new beacon from node " << bsm->getSenderAddress() << std::endl;
    }
    else{
        EV << "Updated existing beacon from node " << bsm->getSenderAddress() << std::endl;
    }
}


void NeighborsTableApp::handleSelfMsg(cMessage* msg)
{
    if (msg == evt_update_nt){
        int expired = nt_manager->expireEntries(beaconInterval);
        if (expired > 0)
            EV << "Deleted " << expired << " neighbors" << std::endl;
        scheduleAt(simTime() + ntUpdateFrequency, evt_update_nt);
    }
    else{
        emit(sigNeighbors_, nt_manager->getNeighborTable().size());
        BeaconingApp::handleSelfMsg(msg);
    }
}

void NeighborsTableApp::handlePositionUpdate(cObject* obj)
{
    BeaconingApp::handlePositionUpdate(obj);
}


NeighborTable::NeighborTable_Neighbor NeighborsTableApp::createNewEntry(BeaconMessage* bsm){
    NeighborTable::NeighborTable_Neighbor entry;
    entry.id = bsm->getSenderAddress();
    entry.position = bsm->getSenderPos();
    entry.speed = bsm->getSenderSpeed();
    return entry;
}


