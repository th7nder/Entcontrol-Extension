// =============================================================
//
// Entcontrol (Navigation.cpp)
// Copyright Raffael 'LeGone' Holz - http://legone.name. All rights reserved.
// Navigation-Parsing-Part: AnthonyIacono - https://github.com/AnthonyIacono
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

#include "Navigation.hpp"
#include "extension.h"
#include "Helper.hpp"

// HLLib
#include "HLLib/HLLibWrapper.hpp"

namespace Navigation
{
	Navigation::INavMesh *gNavMesh;
	unsigned int gHidingSpotsCount;
	std::vector<Navigation::INavMeshHidingSpot*> gHidingSpots;

	/*	
	=============================================================
		Navigation_Load
		Read and parse .nav-files
	=============================================================	
	*/
	bool Load()
	{
		const char *mapname = gamehelpers->GetCurrentMap();
		const char *gamepath = g_pSM->GetGamePath();
		const char *game = g_pSM->GetGameFolderName();

		// Remove all the stored positions
		gHidingSpots.clear();
        printf("deleting gNavMesh\n");
		if (gNavMesh) // Already loaded? Maybe a new map?
			delete gNavMesh;
        printf("deleted gNavMesh\n");
		std::string relativePath, absolutePath;
		absolutePath = gamepath;
		absolutePath += "/maps/";
		absolutePath += mapname;
		absolutePath += ".nav";

		if (!fopen(absolutePath.c_str(), "rb"))
		{
			printf("Navigation: Unable to find navigation mesh: %s\nTrying to extract it from the vpk-file.\n", absolutePath.c_str());

			absolutePath = gamepath;
			if (strcmp(game, "cstrike") == 0)
			{
				absolutePath += "/cstrike_pak_dir.vpk";
			}
			else if (strcmp(game, "csgo") == 0)
			{
				absolutePath += "/csgo_pak_dir.vpk";
			}
			else
			{
				printf("Navigation: Could not find vpk-file for this game/mod.\n");
				return (false);
			}

			if (HLLib::Open(absolutePath.c_str()))
			{
				printf("Navigation: Package %s successfully opened.\n", absolutePath.c_str());

				relativePath = "maps/";
				relativePath += mapname;
				relativePath += ".nav";

				absolutePath = gamepath;
				absolutePath += "/maps";

				if (HLLib::ExtractItem(relativePath.c_str(), absolutePath.c_str()))
				{
					printf("Navigation: %s successfully extracted.\n", relativePath.c_str());
				}
				else
				{
					printf("Navigation: %s could not be found/extracted.\n", relativePath.c_str());

					HLLib::Close();
					return (false);
				}
			}
			else
			{
				printf("Navigation: Package %s could not be found.\n", absolutePath.c_str());

				HLLib::Close();
				return (false);
			}
		}

        printf("hllib close");

		HLLib::Close();

        printf("new Navigation::NavMeshLoader\n");
		Navigation::NavMeshLoader *nav = new Navigation::NavMeshLoader(mapname); 

		char error[1024];
		gNavMesh = nav->Load(error, sizeof(error));
		if(gNavMesh == NULL)
		{
			printf("gNavMeshError, null: %s", error);
			return false;
		}

		// Nav is not needed anylonger
		nav->Destroy();

		if (gNavMesh == NULL)
			return (false);

		return (true);
	}

	/*	
	=============================================================
		Navigation_CachePositions
		Cache positions once and save them into the list. 
		For performance reasons.
	=============================================================	
	*/
	bool CachePositions()
	{
		if (!gNavMesh)
			return (false);

		// Already cached?
		if (gHidingSpots.size() > 0)
			return (true);

		Navigation::IList<Navigation::INavMeshArea*> *areas = gNavMesh->GetAreas();

		unsigned int areaCount = areas->Size();
		for (unsigned int areaI = 0; areaI < areaCount; areaI++)
		{
			// Get all hidingspots
			Navigation::IList<Navigation::INavMeshHidingSpot*> *hidingSpots = areas->At(areaI)->GetHidingSpots();

			unsigned int hidingSpotsCount = hidingSpots->Size();
			for (unsigned int hidingSpotI = 0; hidingSpotI < hidingSpotsCount; hidingSpotI++)
			{
				Navigation::INavMeshHidingSpot *hidingSpot = hidingSpots->At(hidingSpotI);

				gHidingSpots.push_back(hidingSpots->At(hidingSpotI)); // Store the hiding-spot
			}
		}

		// Store once to save performance
		gHidingSpotsCount = gHidingSpots.size();

		// No positions found?
		if (gHidingSpotsCount == 0)
			return (false);

		return (true);
	}

	/*	
	=============================================================
		GetNextHidingSpot
		Increment the list-counter and return the position.
	=============================================================	
	*/
	INavMeshHidingSpot *GetNextHidingSpot()
	{
		static unsigned int posIndex = 0;

		if (posIndex >= gHidingSpotsCount)
			posIndex = 0; // Start from the beginning

		return (gHidingSpots[posIndex++]);
	}
}
