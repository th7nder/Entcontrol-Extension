/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmesh_h__
#define __Navigation_navmesh_h__

#include "INavMesh.h"
#include "../STLish/IList.h"
#include "INavMeshPlace.h"
#include "INavMeshLadder.h"
#include "INavMeshArea.h"

namespace Navigation {
	class NavMesh : public INavMesh {
	public:
		NavMesh(unsigned int magicNumber, unsigned int version, unsigned int subVersion, unsigned int saveBSPSize, bool isMeshAnalyzed,
			IList<INavMeshPlace*> *places, IList<INavMeshArea*> *areas, IList<INavMeshLadder*> *ladders);

		~NavMesh();

		void Destroy();

		unsigned int GetMagicNumber();
		unsigned int GetVersion();
		unsigned int GetSubVersion();
		unsigned int GetSaveBSPSize();
		bool IsMeshAnalyzed();
		IList<INavMeshPlace*> *GetPlaces();
		IList<INavMeshArea*> *GetAreas();
		IList<INavMeshLadder*> *GetLadders();

	private:
		unsigned int magicNumber;
		unsigned int version;
		unsigned int subVersion;
		unsigned int saveBSPSize;
		bool isMeshAnalyzed;
		IList<INavMeshPlace*> *places;
		IList<INavMeshArea*> *areas;
		IList<INavMeshLadder*> *ladders;
	};
}

#endif