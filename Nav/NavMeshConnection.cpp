/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#include "NavMeshConnection.h"

namespace Navigation {
	NavMeshConnection::NavMeshConnection(unsigned int connectingAreaID, NavDirType direction) {
		this->connectingAreaID = connectingAreaID;
		this->direction = direction;
	}

	NavMeshConnection::~NavMeshConnection() {
	}

	void NavMeshConnection::Destroy() {
		delete this;
	}

	unsigned int NavMeshConnection::GetConnectingAreaID() {
		return this->connectingAreaID;
	}

	NavDirType NavMeshConnection::GetDirection() {
		return this->direction;
	}
}