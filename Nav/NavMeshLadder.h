/*	
=============================================================
	Entcontrol - Navigation
	Author: AnthonyIacono - https://github.com/AnthonyIacono
=============================================================	
*/

#ifndef __Navigation_navmeshladder_h__
#define __Navigation_navmeshladder_h__

#include "INavMeshLadder.h"
#include "INavMeshArea.h"

namespace Navigation {
	class NavMeshLadder : public INavMeshLadder {
	public:
		NavMeshLadder(unsigned int id, float width, float length, float topX, float topY, float topZ,
			float bottomX, float bottomY, float bottomZ, NavDirType direction,
			unsigned int topForwardAreaID, unsigned int topLeftAreaID, unsigned int topRightAreaID, unsigned int topBehindAreaID, unsigned int bottomAreaID);

		~NavMeshLadder();

		void Destroy();

		unsigned int GetID();
		float GetWidth();
		float GetLength();

		float GetTopX();
		float GetTopY();
		float GetTopZ();

		float GetBottomX();
		float GetBottomY();
		float GetBottomZ();

		NavDirType GetDirection();
	
		unsigned int GetTopForwardAreaID();
		unsigned int GetTopLeftAreaID();
		unsigned int GetTopRightAreaID();
		unsigned int GetTopBehindAreaID();

		unsigned int GetBottomAreaID();

	private:
		unsigned int id;
		float width;
		float length;
		float topX;
		float topY;
		float topZ;
		float bottomX;
		float bottomY;
		float bottomZ;
		NavDirType direction;
		unsigned int topForwardAreaID;
		unsigned int topLeftAreaID;
		unsigned int topRightAreaID;
		unsigned int topBehindAreaID;
		unsigned int bottomAreaID;
	};
}

#endif