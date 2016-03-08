// =============================================================
//
// Entcontrol (Parser.cpp)
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
#include "HTTP.hpp"
#include "Helper.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <dlib/string.h>
#include "Entity/EntityOutput.hpp"
#include "Nav/Navigation.hpp"

// Updater
#include "LGN/LGN.hpp"

// The maximum-size of this string is relative to the .sp-plugin Oo
char text[131072];

namespace HTTP
{
	namespace Parser
	{
		// Forwards
		IForward *gForwardFunction = NULL;

		bool ForwardFunction(const int userID, std::string &function, std::string &arg, std::string &result)
		{
			if (!gForwardFunction)
			{
				result = "!gForwardFunction";
				return (false);
			}

			if (gForwardFunction->GetFunctionCount() == 0)
			{
				result = "No forward-function found.";
				return (false);
			}

			cell_t status = Pl_Continue;
			gForwardFunction->PushCell(userID);
			gForwardFunction->PushString(function.c_str());
			gForwardFunction->PushString(arg.c_str());
			gForwardFunction->PushStringEx(text, sizeof(text), 0, SM_PARAM_COPYBACK);
			gForwardFunction->Execute(&status);

			if (status == Pl_Continue)
			{
				result = "Unknown function \"" + function + "\"";
				return (false);
			}

			// Return the new (html-)text
			result = text;

			return (true);
		}

		void Line(std::string &line, const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing)
		{
			size_t posStart, posEnd, posTemp;

			// Search for "gets"
			for (posStart = line.find("ec::GET["); posStart != std::string::npos; posStart = line.find("ec::GET["))
			{
				std::string get = &line[posStart+8];
				posEnd = get.find(']');

				get = get.substr(0, posEnd);

				std::string result = incoming.queries[get];
				if (result.empty())
					result = "Unknown GET[" + get + ']';

				// Delete functioncall
				line.erase(posStart, posEnd+9);
				line.insert(posStart, result);
			}

			// Now interpret all functions
			for (posStart = line.find("ec::"); posStart != std::string::npos; posStart = line.find("ec::"))
			{
				std::vector<std::string> params;
				std::string function = &line[posStart+4], arg, result;

				posTemp = function.find('(');
				posEnd = function.find(')');

				arg = function.substr(posTemp+1, posEnd-posTemp-1);
				if (line.find(";") != std::string::npos)
					params = dlib::split(arg.c_str(), ";");
				else
					params.emplace_back(arg);
				function = function.substr(0, posTemp);

				if (function == "GetMapName")
				{
					result = gamehelpers->GetCurrentMap();
				}
				else if (function == "GetGameFolder")
				{
					result = g_pSM->GetGameFolderName();
				}
				else if (function == "GetHTMLFormatedPlayerInfo")
				{
					IGamePlayer *player = Helper::GetPlayerByIP(incoming.foreign_ip);
					if (player)
					{
						result = "<b>" + std::string(player->GetName()) + "</b>";
						result += "<br/>IP: ";
						result += player->GetIPAddress();
						result += "<br/>Auth:";
						result += player->GetAuthString();
						result += "<br/>Steam:";
						result += player->GetSteamAccountID();

						AdminId adminID = player->GetAdminId();
						if (adminID != INVALID_ADMIN_ID)
							result += "<br/>You are an admin";
						else
							result += "<br/>You are no admin";
					}
					else
					{
						result = "You are not connected!";
					}
				}
				else if (function == "GetNavHidingSpots")
				{
					if (Navigation::gNavMesh)
						result = dlib::cast_to_string(Navigation::gHidingSpotsCount);
					else
						result = "Navigation not loaded.";
				}
				else if (function == "GetNavAreas")
				{
					if (Navigation::gNavMesh && Navigation::gNavMesh->GetAreas())
						result = dlib::cast_to_string(Navigation::gNavMesh->GetAreas()->Size());
					else
						result = "Navigation not loaded.";
				}
				else if (function == "GetNavPlaces")
				{
					if (Navigation::gNavMesh && Navigation::gNavMesh->GetPlaces())
						result = dlib::cast_to_string(Navigation::gNavMesh->GetPlaces()->Size());
					else
						result = "Navigation not loaded.";
				}
				else if (function == "GetNavLadders")
				{
					if (Navigation::gNavMesh && Navigation::gNavMesh->GetLadders())
						result = dlib::cast_to_string(Navigation::gNavMesh->GetLadders()->Size());
					else
						result = "Navigation not loaded.";
				}
				else if (function == "GetNavMagicNumber")
				{
					if (Navigation::gNavMesh)
						result = dlib::cast_to_string(Navigation::gNavMesh->GetMagicNumber());
					else
						result = "Navigation not loaded.";
				}
				else if (function == "GetNavSaveBSPSize")
				{
					if (Navigation::gNavMesh)
						result = dlib::cast_to_string(Navigation::gNavMesh->GetSaveBSPSize());
					else
						result = "Navigation not loaded.";
				}
				else if (function == "GetNavVersion")
				{
					if (Navigation::gNavMesh)
						result = dlib::cast_to_string(Navigation::gNavMesh->GetVersion());
					else
						result = "Navigation not loaded.";
				}
				else if (function == "GetNavSubVersion")
				{
					if (Navigation::gNavMesh)
						result = dlib::cast_to_string(Navigation::gNavMesh->GetSubVersion());
					else
						result = "Navigation not loaded.";
				}
				else if (function == "IsLANServer")
				{
					result = gamehelpers->IsLANServer() ? "true" : "false";
				}
				else if (function == "GetMaxClients")
				{
					result = dlib::cast_to_string(playerhelpers->GetMaxClients());
				}
				else if (function == "GetPlayerCount")
				{
					result = dlib::cast_to_string(playerhelpers->GetNumPlayers());
				}
				else if (function == "GetEntityClassname")
				{
					if (params.size() == 1)
					{
						CBaseEntity *entity = gamehelpers->ReferenceToEntity(dlib::string_cast<int>(params.at(0)));
						if (entity)
							result = gamehelpers->GetEntityClassname(entity);
						else
							result = "Entity(" + params.at(0) + ") is invalid!";
					}
					else
					{
						result = "Usage:GetEntityClassname(entity)";
					}
				}
				else if (function == "ServerCommand")
				{
					if (params.size() == 1)
					{
						gamehelpers->ServerCommand(params.at(0).append("\n").c_str());
						result = "";
					}
					else
					{
						result = "Usage:ServerCommand(COMMAND)";
					}
				}
				else if (function == "ReadFile")
				{
					if (params.size() == 1)
					{
						result = HTTP::ReadFile(lastFilePath.substr(0, lastFilePath.find_last_of('/')+1) + params.at(0), incoming, outgoing);
					}
					else
					{
						result = "Usage:ReadFile(filename)";
					}
				}
				else if (function == "MostRecentVersion")
				{
					std::string newVersion;

					newVersion = LGN::get_most_recent_version();
					if (!newVersion.empty())
					{
						result = newVersion;
					}
					else
					{
						result = "Unable to receive the most recent version";
					}
				}
				else if (function == "CurrentVersion")
				{
					result = SMEXT_CONF_VERSION;
				}
				else
				{
					IGamePlayer *player = Helper::GetPlayerByIP(incoming.foreign_ip);
					if (player)
						ForwardFunction(player->GetUserId(), function, arg, result);
					else
						ForwardFunction(0, function, arg, result);
				}

				// Delete functioncallname
				line.erase(posStart, posEnd+5);

				// Insert the result
				line.insert(posStart, result);
			}
		}
	}
}
