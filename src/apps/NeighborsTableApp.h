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

#ifndef APPS_NEIGHBORSTABLEAPP_H_
#define APPS_NEIGHBORSTABLEAPP_H_

#include "veins/veins.h"
#include "BeaconingApp.h"
#include "NeighborTable.h"

using namespace omnetpp;

namespace veins {

class NeighborsTableApp : public BeaconingApp  {
public:
    void initialize(int stage) override;
    virtual ~NeighborsTableApp();
    void finish() override;

protected:
    void onBSM(BeaconMessage* bsm) override;
    //void onWSM(BaseFrame1609_4* wsm) override;
    //void onWSA(DemoServiceAdvertisment* wsa) override;

    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;

    /**
     * Create a new Neighbor Table (NT) entry from the arriving beacon
     */
    NeighborTable::NeighborTable_Neighbor createNewEntry(BeaconMessage* bsm);

protected:
    NeighborTable* nt_manager;
    cMessage* evt_update_nt;
    double ntUpdateFrequency;
    simsignal_t sigNeighbors_;
};

} // namespace veins

#endif /* APPS_NEIGHBORSTABLEAPP_H_ */
