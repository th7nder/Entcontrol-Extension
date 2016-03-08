// =============================================================
//
// Entcontrol (Navigation.hpp)
// Copyright Raffael 'LeGone' Holz - http://legone.name. All rights reserved.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License, version 3.0, as published by the
// Free Software Foundation.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see <http://www.gnu.org/licenses/>.
//
// =============================================================

#include <vector>
#include "Nav/NavMeshLoader.h"

namespace Navigation
{
	extern INavMesh *gNavMesh;
	extern unsigned int gHidingSpotsCount;
	extern std::vector<INavMeshHidingSpot*> gHidingSpots;

	bool Load();
	bool CachePositions();
	INavMeshHidingSpot *GetNextHidingSpot();
}