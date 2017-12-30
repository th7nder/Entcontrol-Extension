/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_inavmeshcornerlightintensity_h__
#define __Navigation_inavmeshcornerlightintensity_h__

#include "NavCornerType.h"

namespace Navigation {
	/**
	 * Represents a loaded navigation mesh area corner light intensity.
	 */
	class INavMeshCornerLightIntensity {
	public:
		virtual ~INavMeshCornerLightIntensity() {};
		/**
		 * Destroy the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Retrieve the corner type.
		 */
		virtual NavCornerType GetCornerType() = 0;

		/**
		 * Retrieve the light intesity value.
		 */
		virtual float GetLightIntensity() = 0;
	};
}

#endif