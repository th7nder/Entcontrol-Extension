/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshhidingspot_h__
#define __Navigation_navmeshhidingspot_h__

#include "INavMeshHidingSpot.h"

namespace Navigation {
	class NavMeshHidingSpot : public INavMeshHidingSpot {
	public:
		NavMeshHidingSpot(unsigned int id, float x, float y, float z, unsigned char flags);
		~NavMeshHidingSpot();

		void Destroy();

		unsigned int GetID();

		float GetX();
		float GetY();
		float GetZ();

		unsigned char GetFlags();

	private:
		unsigned int id;
		float x;
		float y;
		float z;
		unsigned char flags;
	};
}

#endif