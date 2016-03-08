/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshencounterspot_h__
#define __Navigation_navmeshencounterspot_h__

#include "INavMeshEncounterSpot.h"

namespace Navigation {
	class NavMeshEncounterSpot : public INavMeshEncounterSpot {
	public:
		NavMeshEncounterSpot(unsigned int orderID, float parametricDistance);
		~NavMeshEncounterSpot();

		void Destroy();

		unsigned int GetOrderID();
		float GetParametricDistance();

	private:
		unsigned int orderID;
		float parametricDistance;
	};
}

#endif