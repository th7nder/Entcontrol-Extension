/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshencounterpath_h__
#define __Navigation_navmeshencounterpath_h__

#include "INavMeshEncounterPath.h"
#include "INavMeshEncounterSpot.h"
#include "NavDirType.h"

namespace Navigation {
	class NavMeshEncounterPath : public INavMeshEncounterPath {
	public:
		NavMeshEncounterPath(unsigned int fromAreaID, NavDirType fromDirection, unsigned int toAreaID, NavDirType toDirection, IList<INavMeshEncounterSpot*> *encounterSpots);
		~NavMeshEncounterPath();

		void Destroy();

		unsigned int GetFromAreaID();
		NavDirType GetFromDirection();
		unsigned int GetToAreaID();
		NavDirType GetToDirection();
		IList<INavMeshEncounterSpot*> *GetEncounterSpots();

	private:
		unsigned int fromAreaID;
		NavDirType fromDirection;
		unsigned int toAreaID;
		NavDirType toDirection;
		IList<INavMeshEncounterSpot*> *encounterSpots;
	};
}

#endif