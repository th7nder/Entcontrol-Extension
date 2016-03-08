/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshconnection_h__
#define __Navigation_navmeshconnection_h__

#include "INavMeshConnection.h"

namespace Navigation {
	class NavMeshConnection : public INavMeshConnection {
	public:
		NavMeshConnection(unsigned int connectingAreaID, NavDirType direction);
		~NavMeshConnection();

		void Destroy();

		unsigned int GetConnectingAreaID();
		NavDirType GetDirection();

	private:
		unsigned int connectingAreaID;
		NavDirType direction;
	};
}

#endif