/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_inavmash_h__
#define __Navigation_inavmash_h__

#include "../STLish/IList.h"
#include "INavMeshPlace.h"
#include "INavMeshArea.h"
#include "INavMeshLadder.h"

namespace Navigation {
	/**
	 * Represents a loaded navigation mesh file.
	 */
	class INavMesh {
	public:
		virtual ~INavMesh() {};
		/**
		 * Destroys the instance.
		 */
		virtual void Destroy() = 0;

		/**
		 * Retrieves the magic number.
		 */
		virtual unsigned int GetMagicNumber() = 0;
		
		/**
		 * Retrieves the version number.
		 */
		virtual unsigned int GetVersion() = 0;

		/**
		 * Retrieves the sub-version number.
		 */
		virtual unsigned int GetSubVersion() = 0;

		/**
		 * Retrieves the BSP's save size.
		 */
		virtual unsigned int GetSaveBSPSize() = 0;
		
		/**
		 * Returns if the mesh has been analyzed.
		 */
		virtual bool IsMeshAnalyzed() = 0;
		
		/**
		 * Retrieve a list of loaded places inside the mesh.
		 */
		virtual IList<INavMeshPlace*> *GetPlaces() = 0;

		/**
		 * Retrieve a list of loaded geometric areas inside the mesh.
		 */
		virtual IList<INavMeshArea*> *GetAreas() = 0;

		/**
		 * Retrieve a list of loaded ladders inside the mesh.
		 */
		virtual IList<INavMeshLadder*> *GetLadders() = 0;
	};
}

#endif