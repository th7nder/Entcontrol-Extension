// =============================================================
//
// Entcontrol (natives.cpp)
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
#include "Entity/EntityOutput.hpp"
#include "Helper.hpp"

// Navigation
#include "Nav/Navigation.hpp"

// HLLib
#include "HLLib/HLLibWrapper.hpp"

// Webserver
#include "Webserver/HTTP.hpp"

// Bugs - Report to MantisBT
#include "Bugs/Bugs.hpp"

// Dlib
// + Workaround
#undef COMPILE_TIME_ASSERT
#define COMPILE_TIME_ASSERT(value)
// - Workaround
#include <dlib/crc32.h>
#include <dlib/md5.h>
#include <dlib/hash.h>

/*
=============================================================
	Output-Event-Stuff
=============================================================
*/
inline Entity::CBaseEntityOutput *GetOutput(CBaseEntity *pEntity, const char *sOutput)
{
	int dmap = Helper::Entity::GetDataMapOffset(pEntity, sOutput);

	if (dmap == -1)
		return (NULL);

	return ((Entity::CBaseEntityOutput *)((int)pEntity + (int)dmap));
}

cell_t Entity_GetOutputCount(IPluginContext *pContext, const cell_t *params)
{
	char *sOutput;
	pContext->LocalToString(params[2], &sOutput);

	CBaseEntity *pEntity = Helper::Entity::GetCBaseEntity(params[1]);
	Entity::CBaseEntityOutput *pOutput = GetOutput(pEntity, sOutput);

	if (pOutput == NULL)
		return (0);

	return (pOutput->NumberOfElements());
}

cell_t Entity_GetOutputFirst(IPluginContext *pContext, const cell_t *params)
{
	char *sOutput;
	pContext->LocalToString(params[2], &sOutput);

	CBaseEntity *pEntity = Helper::Entity::GetCBaseEntity(params[1]);
	Entity::CBaseEntityOutput *pOutput = GetOutput(pEntity, sOutput);

	if (pOutput == NULL || pOutput->m_ActionList == NULL)
		return (false);

	pContext->StringToLocal(params[2], strlen(pOutput->m_ActionList->m_iTarget.ToCStr())+1, pOutput->m_ActionList->m_iTarget.ToCStr());

	return (true);
}

cell_t Entity_GetOutputAt(IPluginContext *pContext, const cell_t *params)
{
	char *sOutput;
	pContext->LocalToString(params[2], &sOutput);

	CBaseEntity *pEntity = Helper::Entity::GetCBaseEntity(params[1]);
	Entity::CBaseEntityOutput *pOutput = GetOutput(pEntity, sOutput);

	if (pOutput == NULL || pOutput->m_ActionList == NULL)
		return (false);

	Entity::CEventAction *actionList = pOutput->m_ActionList;
	for (int i = 0; i < params[3]; i++)
		actionList->m_pNext;

	pContext->StringToLocal(params[2], strlen(pOutput->m_ActionList->m_iTarget.ToCStr())+1, pOutput->m_ActionList->m_iTarget.ToCStr());

	return (true);
}

/*
=============================================================
	Navigation_Load
	Read and parse .nav-files
=============================================================
*/
cell_t Navigation_Load(IPluginContext *pContext, const cell_t *params)
{
	return (Navigation::Load());
}

/*
=============================================================
	Navigation_CachePositions
	Cache positions once and save them into the list. 
	For performance reasons.
=============================================================
*/
cell_t Navigation_CachePositions(IPluginContext *pContext, const cell_t *params)
{
	return (Navigation::CachePositions());
}

/*
=============================================================
	Navigation_GetNextHidingSpot
	Increment the list-counter and return the position.
=============================================================
*/
cell_t Navigation_GetNextHidingSpot(IPluginContext *pContext, const cell_t *params)
{

	// TO DO
	/*cell_t *pos;
	pContext->LocalToPhysAddr(params[1], &pos);

	Navigation::INavMeshHidingSpot *hidingSpot = Navigation::GetNextHidingSpot();

	pos[0] = sp_ftoc(hidingSpot->GetX());
	pos[1] = sp_ftoc(hidingSpot->GetY());
	pos[2] = sp_ftoc(hidingSpot->GetZ());*/

	return (true);
}

/*
=============================================================
	Webserver_GetPort
	Get port of webserver
=============================================================
*/
cell_t Webserver_GetPort(IPluginContext *pContext, const cell_t *params)
{
	return (HTTP::GetPort());
}

/*
=============================================================
	Webserver_GetIP
	Get IP-address of webserver
=============================================================
*/
cell_t Webserver_GetIP(IPluginContext *pContext, const cell_t *params)
{
	const char *buffer = HTTP::GetIP();

	pContext->StringToLocal(params[1], strlen(buffer)+1, buffer);

	return (0);
}

/*
=============================================================
	HLLib_OpenFile
	Open File
=============================================================
*/
cell_t HLLib_OpenFile(IPluginContext *pContext, const cell_t *params)
{
	char *file;
	pContext->LocalToString(params[1], &file);

	return (HLLib::Open(file));
}

/*
=============================================================
	HLLib_Close
	Close File
=============================================================
*/
cell_t HLLib_Close(IPluginContext *pContext, const cell_t *params)
{
	HLLib::Close();

	return (0);
}

/*
=============================================================
	HLLib_ItemExist
	Check if item exists
=============================================================
*/
cell_t HLLib_ItemExist(IPluginContext *pContext, const cell_t *params)
{
	char *item;
	pContext->LocalToString(params[1], &item);

	return (HLLib::FindItem(item));
}

/*
=============================================================
	HLLib_Extract
	Extract item
=============================================================
*/
cell_t HLLib_Extract(IPluginContext *pContext, const cell_t *params)
{
	char *source, *destination;
	pContext->LocalToString(params[1], &source);
	pContext->LocalToString(params[2], &destination);

	return (HLLib::ExtractItem(source, destination));
}

/*
=============================================================
	Dlib_CRC32
	CRC32
=============================================================
*/
cell_t Dlib_CRC32(IPluginContext *pContext, const cell_t *params)
{
	char *item;
	pContext->LocalToString(params[1], &item);

	std::string crc32 = dlib::cast_to_string(dlib::crc32(item).get_checksum());
	pContext->StringToLocal(params[1], crc32.length()+1, crc32.c_str());

	return (0);
}

/*
=============================================================
	Dlib_MD5
	MD5
=============================================================
*/
cell_t Dlib_MD5(IPluginContext *pContext, const cell_t *params)
{
	char *item;
	pContext->LocalToString(params[1], &item);

	std::string md5 = dlib::md5(item);
	pContext->StringToLocal(params[1], md5.length()+1, md5.c_str());

	return (0);
}

/*
=============================================================
	Dlib_HammingDistance
	Hamming Distance
=============================================================
*/
cell_t Dlib_HammingDistance(IPluginContext *pContext, const cell_t *params)
{
	return (dlib::hamming_distance(params[1], params[2]));
}

/*
=============================================================
	Dlib_Hash
	Hash
=============================================================
*/
cell_t Dlib_Hash(IPluginContext *pContext, const cell_t *params)
{
	char *item;
	pContext->LocalToString(params[1], &item);

	std::string hash = dlib::cast_to_string(dlib::hash(item));
	pContext->StringToLocal(params[1], hash.length()+1, hash.c_str());

	return (0);
}

/*
=============================================================
	Dlib_GaussianRandomHash
	Gaussian Random Hash
=============================================================
*/
cell_t Dlib_GaussianRandomHash(IPluginContext *pContext, const cell_t *params)
{
	return (sp_ftoc(dlib::gaussian_random_hash(params[1], params[2], params[3])));
}

/*
=============================================================
	ReportBug
	Report EntControl-Bug
=============================================================
*/
cell_t ReportBug(IPluginContext *pContext, const cell_t *params)
{
	char description[1024], *summary;
	pContext->LocalToString(params[1], &summary);
	smutils->FormatString(description, sizeof(description), pContext, params, 2);

	Bugs::ReportToMantisBT(plsys->FindPluginByContext(pContext->GetContext())->GetPublicInfo()->name, summary, description);
	return (0);
}

sp_nativeinfo_t natives[] = 
{
	{"EC_Entity_GetOutputCount",		Entity_GetOutputCount},
	{"EC_Entity_GetOutputFirst",		Entity_GetOutputFirst},
	{"EC_Entity_GetOutputAt",			Entity_GetOutputAt},
	{"EC_Nav_Load",						Navigation_Load},
	{"EC_Nav_CachePositions",			Navigation_CachePositions},
	{"EC_Nav_GetNextHidingSpot",		Navigation_GetNextHidingSpot},
	{"EC_Web_GetPort",					Webserver_GetPort},
	{"EC_Web_GetIP",					Webserver_GetIP},
	{"EC_HLLib_OpenFile",				HLLib_OpenFile},
	{"EC_HLLib_ItemExist",				HLLib_ItemExist},
	{"EC_HLLib_Extract",				HLLib_Extract},
	{"EC_HLLib_Close",					HLLib_Close},
	{"EC_Dlib_CRC32",					Dlib_CRC32},
	{"EC_Dlib_MD5",						Dlib_MD5},
	{"EC_Dlib_HammingDistance",			Dlib_HammingDistance},
	{"EC_Dlib_Hash",					Dlib_Hash},
	{"EC_Dlib_GaussianRandomHash",		Dlib_GaussianRandomHash},
	{"EC_ReportBug",					ReportBug},
	{NULL,								NULL},
};
