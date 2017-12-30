/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_inavmeshloader_h__
#define __Navigation_inavmeshloader_h__

#include "INavMesh.h"

namespace Navigation {
	/**
	 * Represents a Source Engine navigation mesh loader.
	 */
	class INavMeshLoader {
	public:
		virtual ~INavMeshLoader() {};
		/**
		 * Destroy the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Load a navigation mesh, errors are outputted to error and will be truncated to errorMaxlen.
		 */
		virtual INavMesh *Load(char *error, int errorMaxlen) = 0;
	};
}

#endif