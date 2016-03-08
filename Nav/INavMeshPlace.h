/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_inavmeshplace_h__
#define __Navigation_inavmeshplace_h__

namespace Navigation {
	/**
	 * Represents a loaded place within a navigation mesh.
	 */
	class INavMeshPlace {
	public:
		/**
		 * Destroy the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Retrieve the place's name.
		 */
		virtual const char *GetName() = 0;

		/**
		 * Retrieve the place's ID.
		 */
		virtual unsigned int GetID() = 0;
	};
}

#endif