/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#include "NavMesh.h"
#include "stdio.h"
namespace Navigation {
	NavMesh::NavMesh(unsigned int magicNumber, unsigned int version, unsigned int subVersion, unsigned int saveBSPSize, bool isMeshAnalyzed,
		IList<INavMeshPlace*> *places, IList<INavMeshArea*> *areas, IList<INavMeshLadder*> *ladders) {
			this->magicNumber = magicNumber;
			this->version = version;
			this->subVersion = subVersion;
			this->saveBSPSize = saveBSPSize;
			this->isMeshAnalyzed = isMeshAnalyzed;
			this->places = places;
			this->areas = areas;
			this->ladders = ladders;
	}

	NavMesh::~NavMesh() {
	    printf("navmesh destroy\n");
    	unsigned int placeCount = this->places->Size();

		for(unsigned int placeIndex = 0; placeIndex < placeCount; placeIndex++) {
			INavMeshPlace *place = this->places->At(placeIndex);

			place->Destroy();
		}
        
        printf("place destroy\n");

		this->places->Destroy();

        printf("places destroy\n");

		unsigned int areaCount = this->areas->Size();

		for(unsigned int areaIndex = 0; areaIndex < placeCount; areaIndex++) {	
            printf("accessing area %d\n", areaIndex);
            INavMeshArea *area = this->areas->At(areaIndex);
            printf("destroying area %d\n", areaIndex);
			area->Destroy();
		}

        printf("area destroyed\n");
		
		this->areas->Destroy();

        printf("areas destroy\n");

		unsigned int ladderCount = this->ladders->Size();

		for(unsigned int ladderIndex = 0; ladderIndex < ladderCount; ladderIndex++) {
			INavMeshLadder *ladder = this->ladders->At(ladderIndex);

			ladder->Destroy();
		}

        printf("ladder destroy\n");

		this->ladders->Destroy();
        printf("ladders destroyed\n");
	}

	void NavMesh::Destroy() {
		delete this;
	}

	unsigned int NavMesh::GetMagicNumber() {
		return this->magicNumber;
	}

	unsigned int NavMesh::GetVersion() {
		return this->version;
	}

	unsigned int NavMesh::GetSubVersion() {
		return this->subVersion;
	}

	unsigned int NavMesh::GetSaveBSPSize() {
		return this->saveBSPSize;
	}

	bool NavMesh::IsMeshAnalyzed() {
		return this->isMeshAnalyzed;
	}

	IList<INavMeshPlace*> *NavMesh::GetPlaces() {
		return this->places;
	}

	IList<INavMeshArea*> *NavMesh::GetAreas() {
		return this->areas;
	}

	IList<INavMeshLadder*> *NavMesh::GetLadders() {
		return this->ladders;
	}
}
