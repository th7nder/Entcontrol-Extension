/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshcornerlightintensity_h__
#define __Navigation_navmeshcornerlightintensity_h__

#include "INavMeshCornerLightIntensity.h"

namespace Navigation {
	class NavMeshCornerLightIntensity : public INavMeshCornerLightIntensity {
	public:
		NavMeshCornerLightIntensity(NavCornerType cornerType, float lightIntensity);
		~NavMeshCornerLightIntensity();

		void Destroy();

		NavCornerType GetCornerType();
		float GetLightIntensity();

	private:
		NavCornerType cornerType;
		float lightIntensity;
	};
}

#endif