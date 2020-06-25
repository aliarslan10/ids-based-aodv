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

package ali_aodv;

network flatTopoloji
{
    parameters:

		// int n @prompt("Number of nodes") = default(10);

        int dugumSayisi;
        int kaynak;
        int hedef;
        int kapsama;
        volatile double posX = intuniform (100,600);
        volatile double posY = intuniform (100,200);

        @display("bgb=700,300");

    submodules:
        n[dugumSayisi]: Dugum {

            parameters:
                @display("p=35,20;is=vs;r=70,,#EBEBFF");
        }
}

