/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_inavmeshvisiblearea_h__
#define __Navigation_inavmeshvisiblearea_h__

namespace Navigation {
	/**
	 * Represents a visible area within (from) an area.
	 */
	class INavMeshVisibleArea {
	public:
		virtual ~INavMeshVisibleArea() {};
		/**
		 * Destroy the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Retrieve the visible area ID.
		 */
		virtual unsigned int GetVisibleAreaID() = 0;

		/**
		 * Retrieve the attributes.
		 */
		virtual unsigned char GetAttributes() = 0;
	};
}

#endif