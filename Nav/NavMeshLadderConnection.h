/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshladderconnection_h__
#define __Navigation_navmeshladderconnection_h__

#include "INavMeshLadderConnection.h"

namespace Navigation {
	class NavMeshLadderConnection : public INavMeshLadderConnection {
	public:
		NavMeshLadderConnection(unsigned int connectingLadderID, NavLadderDirType direction);
		~NavMeshLadderConnection();

		void Destroy();

		unsigned int GetConnectingLadderID();
		NavLadderDirType GetDirection();
	
	private:
		unsigned int connectingLadderID;
		NavLadderDirType direction;
	};
}

#endif