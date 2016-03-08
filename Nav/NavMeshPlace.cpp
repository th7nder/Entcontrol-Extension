/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#include "NavMeshPlace.h"
#include <string.h>

namespace Navigation {
	NavMeshPlace::NavMeshPlace(unsigned int id, const char *name) {
		this->id = id;
		strcpy(this->name, name);
	}

	NavMeshPlace::~NavMeshPlace() {
	}

	void NavMeshPlace::Destroy() {
		delete this;
	}

	const char *NavMeshPlace::GetName() {
		return this->name;
	}

	unsigned int NavMeshPlace::GetID() {
		return this->id;
	}
}