/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshvisiblearea_h__
#define __Navigation_navmeshvisiblearea_h__

#include "INavMeshVisibleArea.h"

namespace Navigation {
	class NavMeshVisibleArea : public INavMeshVisibleArea {
	public:
		NavMeshVisibleArea(unsigned int visibleAreaID, unsigned char attributes);
		~NavMeshVisibleArea();

		void Destroy();

		unsigned int GetVisibleAreaID();
		unsigned char GetAttributes();

	private:
		unsigned int visibleAreaID;
		unsigned char attributes;
	};
}

#endif