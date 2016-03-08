/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#include "NavMeshVisibleArea.h"

namespace Navigation {
	NavMeshVisibleArea::NavMeshVisibleArea(unsigned int visibleAreaID, unsigned char attributes) {
		this->visibleAreaID = visibleAreaID;
		this->attributes = attributes;
	}

	NavMeshVisibleArea::~NavMeshVisibleArea() {
	}
	
	void NavMeshVisibleArea::Destroy() {
		delete this;
	}

	unsigned int NavMeshVisibleArea::GetVisibleAreaID() {
		return this->visibleAreaID;
	}

	unsigned char NavMeshVisibleArea::GetAttributes() {
		return this->attributes;
	}
}