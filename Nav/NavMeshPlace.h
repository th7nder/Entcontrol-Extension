/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshplace_h__
#define __Navigation_navmeshplace_h__

#include "INavMeshPlace.h"

namespace Navigation {
	class NavMeshPlace : public INavMeshPlace {
	public:
		NavMeshPlace(unsigned int id, const char *name);
		~NavMeshPlace();
		
		void Destroy();

		const char *GetName();
		unsigned int GetID();

	private:
		unsigned int id;
		char name[256];
	};
}

#endif