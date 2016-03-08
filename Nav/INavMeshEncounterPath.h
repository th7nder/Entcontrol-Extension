/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_inavmeshencounterpath_h__
#define __Navigation_inavmeshencounterpath_h__

#include "NavDirType.h"
#include "../STLish/IList.h"
#include "INavMeshEncounterSpot.h"

namespace Navigation {
	/**
	 * Represents a loaded navigation mesh encounter path.
	 */
	class INavMeshEncounterPath {
	public:
		/**
		 * Destroys the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Retrieve the "from" area ID.
		 */
		virtual unsigned int GetFromAreaID() = 0;

		/**
		 * Retrieve the "from" direction.
		 */
		virtual NavDirType GetFromDirection() = 0;

		/**
		 * Retrieve the "to" area ID.
		 */
		virtual unsigned int GetToAreaID() = 0;

		/**
		 * Retrieve the "to" area direction.
		 */
		virtual NavDirType GetToDirection() = 0;

		/**
		 * Retrieve a list of loaded encounter spots.
		 */
		virtual IList<INavMeshEncounterSpot*> *GetEncounterSpots() = 0;
	};
}

#endif