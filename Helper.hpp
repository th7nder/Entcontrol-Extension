// =============================================================
//
// Entcontrol (helper.hpp)
// Copyright Raffael Holz aka. LeGone. All rights reserved.
// http://www.legone.name
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

#include "extension.h"
#include <iostream>
#include <string>
#include <algorithm>

namespace Helper
{
	namespace Log
	{
		void Error(const char *, const char *, long, std::string);
	}

	inline bool internal_string_check(char c)
	{
		return !(isalpha(c) || isdigit(c) || c=='_');
	}

	inline void GetCleanString(std::string &stringToBeCleaned)
	{
		stringToBeCleaned.erase(std::remove_if(stringToBeCleaned.begin(), stringToBeCleaned.end(), internal_string_check), stringToBeCleaned.end());
	}

	inline AdminId FindInGameAdminIDByClientIP(std::string ip)
	{
		char playercount = playerhelpers->GetNumPlayers();
		for (char i=1; i<=playercount; i++)
		{
			IGamePlayer *player = playerhelpers->GetGamePlayer(i);

			std::string ingameIP = player->GetIPAddress();
			ingameIP = ingameIP.substr(0, ingameIP.find(':'));

			if ((player && ingameIP == ip) || ip == "127.0.0.1")
			{
				// Player is ingame
				return (player->GetAdminId());
			}
		}

		return (INVALID_ADMIN_ID);
	}

	inline IGamePlayer *GetPlayerByIP(std::string ip)
	{
		char playercount = playerhelpers->GetNumPlayers();
		for (char i=1; i<=playercount; i++)
		{
			IGamePlayer *player = playerhelpers->GetGamePlayer(i);

			std::string ingameIP = player->GetIPAddress();
			ingameIP = ingameIP.substr(0, ingameIP.find(':'));

			if ((player && ingameIP == ip) || ip == "127.0.0.1")
			{
				// Player is ingame
				return (player);
			}
		}

		return (NULL);
	}

	namespace Entity
	{
		// Taken from SourceMod Counter-Strike:Source Extension
		inline CBaseEntity *GetCBaseEntity(int num)
		{
#if SOURCE_ENGINE >= SE_LEFT4DEAD
			edict_t *pEdict = (edict_t *)(gpGlobals->pEdicts + num);
#else
			edict_t *pEdict = engine->PEntityOfEntIndex(num);
#endif
			if (!pEdict || pEdict->IsFree())
				return (NULL);

			IServerUnknown *pUnk;
			if ((pUnk=pEdict->GetUnknown()) == NULL)
				return (NULL);

			return (pUnk->GetBaseEntity());
		}

		inline int GetDataMapOffset(CBaseEntity *pEnt, const char *name)
		{
			datamap_t *pMap = gamehelpers->GetDataMap(pEnt);
			if (!pMap)
				return (-1);

			typedescription_t *typedesc = gamehelpers->FindInDataMap(pMap, name);

			if (typedesc == NULL)
				return (-1);

#if SOURCE_ENGINE >= SE_LEFT4DEAD
			return (typedesc->fieldOffset);
#else
			return (typedesc->fieldOffset[TD_OFFSET_NORMAL]);
#endif
		}
	}
}
