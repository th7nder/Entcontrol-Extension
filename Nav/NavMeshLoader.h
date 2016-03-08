/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshloader_h__
#define __Navigation_navmeshloader_h__

#include "INavMeshLoader.h"
#include "INavMesh.h"
#include <iostream>

namespace Navigation {
	class NavMeshLoader : public INavMeshLoader {
	public:
		NavMeshLoader(const char *mapName);
		~NavMeshLoader();

		void Destroy();
		INavMesh *Load(char *error, int errorMaxlen);
	
	private:
		unsigned int ReadData(void *output, unsigned int elementSize, unsigned int elementCount, FILE *fileHandle);

	private:
		char mapName[100];
		unsigned int bytesRead;
	};
}

#endif