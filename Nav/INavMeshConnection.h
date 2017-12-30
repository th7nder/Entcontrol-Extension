/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_inavmeshconnection_h__
#define __Navigation_inavmeshconnection_h__

#include "NavDirType.h"

namespace Navigation {
	/**
	 * Represents a loaded navigation mesh area connection.
	 */
	class INavMeshConnection {
	public:
		virtual ~INavMeshConnection() {};
		/**
		 * Destroy the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Retrieve the connecting area ID.
		 */
		virtual unsigned int GetConnectingAreaID() = 0;
		
		/**
		 * Retrieve the connection direction.
		 */
		virtual NavDirType GetDirection() = 0;
	};
}

#endif