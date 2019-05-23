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

package veins_nt_manager.apps;
import veins_nt_manager.apps.BeaconingApp;


simple NeighborsTableApp extends BeaconingApp
{
    @class(veins::NeighborsTableApp);
    string appName = default("Neighbors Table App");
 	double ntUpdateFrequency = default(0.01);
 	
 	@signal[sigNeighbors];
    @statistic[statNeighbors](title="Number of neighbors in the NT"; unit=""; source="sigNeighbors"; record=mean,vector);
}