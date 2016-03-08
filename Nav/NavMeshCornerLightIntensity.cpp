/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#include "NavMeshCornerLightIntensity.h"

namespace Navigation {
	NavMeshCornerLightIntensity::NavMeshCornerLightIntensity(NavCornerType cornerType, float lightIntensity) {
		this->cornerType = cornerType;
		this->lightIntensity = lightIntensity;
	}

	NavMeshCornerLightIntensity::~NavMeshCornerLightIntensity() {
	}

	void NavMeshCornerLightIntensity::Destroy() {
		delete this;
	}

	NavCornerType NavMeshCornerLightIntensity::GetCornerType() {
		return this->cornerType;
	}

	float NavMeshCornerLightIntensity::GetLightIntensity() {
		return this->lightIntensity;
	}
}