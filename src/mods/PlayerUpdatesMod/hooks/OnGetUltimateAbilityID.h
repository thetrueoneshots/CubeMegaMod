/*
* Hook for modifying the ultimate ability ID.
*/
#pragma once

#include "cwsdk.h"
#include "../PlayerUpdatesMod.h"

extern "C" int OnGetUltimateAbilityID(cube::Creature* player) {
	switch (player->entity_data.classType)
	{
	case 1:
	{
		return 148 + (player->entity_data.specialization > 0 ? 1 : 0);
	}
	case 2:
	{
		return 143 - (player->entity_data.specialization > 0 ? 1 : 0);
	}
	case 3:
	{
		if (player->entity_data.specialization == 0)
		{
			return 47;
		}
		return 144;
	}
	case 4:
	{
		if (player->entity_data.specialization == 0)
		{
			return 109;
		}
		return 141;
	}
	default:
	{
		int index = player->entity_data.classType - 5;
		if (index < 0 || index >= MOD->m_Classes.size())
		{
			return 0;
		}
		
		return MOD->m_Classes.at(index)->GetUltimateAbilityId(player);
	}
	}
	return 0;
}

__attribute__((naked)) void ASMOnGetUltimateAbilityID() {
	asm(".intel_syntax \n"

		"call OnGetUltimateAbilityID \n"
		"retn \n"

		".att_syntax \n"
	);
}

void InitializeOnGetUltimateIDHandler()
{
	WriteFarJMP(CWOffset(0x656E0), (void*)&ASMOnGetUltimateAbilityID);
}