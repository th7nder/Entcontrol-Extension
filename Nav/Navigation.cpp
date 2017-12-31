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
	unsigned int gHidingSpotsCount;
	INavFile navFile;


	bool getPath(std::string& target)
	{
		const char *mapname = gamehelpers->GetCurrentMap();
		const char *gamepath = g_pSM->GetGamePath();
		const char *game = g_pSM->GetGameFolderName();

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
				return false;
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

		HLLib::Close();

		char navPath[1024];
		g_pSM->BuildPath(Path_Game, navPath, sizeof(navPath), "maps\\%s.nav", mapname);
		target = navPath;
		return true;
	}

	/*	
	=============================================================
		Navigation_Load
		Read and parse .nav-files
	=============================================================	
	*/
	bool Load()
	{
		
		navFile.RestoreDefaults();
		std::string navPath;
		if(!getPath(navPath))
		{
			std::cerr << "[EC] Couldn't get nav path for this map" << '\n';
			return false;
		}

		std::cout << "[DEBUG] navPath found: " << navPath << '\n';

       		std::ifstream ifs(navPath, std::ios::binary);

		if (!ifs.is_open())
		{
			std::cerr << "[EC] Couldn't open nav file" << '\n';
			return false;
		}

		if (!navFile.Load(ifs))
		{
			std::cerr << "[EC] Couldn't load nav file" << '\n';
			return false;
		}

		ifs.close();

		std::cout << "[DEBUG] Successfully loaded nav data" << '\n';
	
		return true;
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

		// Already cached?
		//if (gHidingSpots.size() > 0)
		//	return (true);

		/*Navigation::IList<Navigation::INavMeshArea*> *areas = gNavMesh->GetAreas();

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

		return (true);*/

		return false;
	}

	/*	
	=============================================================
		GetNextHidingSpot
		Increment the list-counter and return the position.
	=============================================================	
	*/
	/*INavMeshHidingSpot *GetNextHidingSpot()
	{
		static unsigned int posIndex = 0;

		if (posIndex >= gHidingSpotsCount)
			posIndex = 0; // Start from the beginning

		return (gHidingSpots[posIndex++]);
	}*/
}
