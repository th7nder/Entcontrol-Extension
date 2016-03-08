// =============================================================
//
// Entcontrol (EntityOutput.cpp)
// Copyright Raffael Holz aka. LeGone. All rights reserved.
// http://www.legone.name
// Special thanks to Matt Woodrow for his CEntity Entity Handling Framework
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

#define NULL 0
#include "EntityOutput.hpp"
#include "isaverestore.h"

namespace Entity
{
	//extern ISaveRestoreOps *variantFuncs;

	BEGIN_SIMPLE_DATADESC( CEventAction )
		DEFINE_FIELD( m_iTarget, FIELD_STRING ),
		DEFINE_FIELD( m_iTargetInput, FIELD_STRING ),
		DEFINE_FIELD( m_iParameter, FIELD_STRING ),
		DEFINE_FIELD( m_flDelay, FIELD_FLOAT ),
		DEFINE_FIELD( m_nTimesToFire, FIELD_INTEGER ),
		DEFINE_FIELD( m_iIDStamp, FIELD_INTEGER ),
	END_DATADESC()

	BEGIN_SIMPLE_DATADESC( CBaseEntityOutput )
		//DEFINE_CUSTOM_FIELD( m_Value, variantFuncs ),
	END_DATADESC()

	int CBaseEntityOutput::NumberOfElements(void)
	{
		int count = 0;

		if (m_ActionList == NULL)
			return (-1);

		for (CEventAction *ev = m_ActionList; ev != NULL; ev = ev->m_pNext)
			count++;

		return (count);
	}
}