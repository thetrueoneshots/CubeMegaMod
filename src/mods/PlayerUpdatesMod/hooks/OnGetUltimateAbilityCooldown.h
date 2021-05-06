/*
* Hook for modifying the ultimate ability ID.
*/
#pragma once

#include "cwsdk.h"
#include "../PlayerUpdatesMod.h"

std::vector<int> cooldownMap;

void SetCooldown(const std::vector<int>& ids, int cooldown) {
	for (auto i = 0; i < ids.size(); i++) {
		cooldownMap.at(ids[i]) = cooldown;
	}
}

void SetupCooldowns() {
	SetCooldown(std::vector<int>({ 51, 55, 115 }), 16000);
	SetCooldown(std::vector<int>({ 47, 109, 112, 113, 114, 142, 144, 146, 165 }), 40000);
	SetCooldown(std::vector<int>({ 95, 98, 136, 149 }), 30000);
	SetCooldown(std::vector<int>({ 22, 52, 97 }), 12000);
	SetCooldown(std::vector<int>({ 111 }), 4000);
	SetCooldown(std::vector<int>({ 73 }), 15000);
	SetCooldown(std::vector<int>({ 140, 141, 143 }), 60000);
	SetCooldown(std::vector<int>({ 148 }), 20000);
	SetCooldown(std::vector<int>({ 50, 108 }), 16000);
}

extern "C" int OnGetUltimateAbilityCooldown(cube::Creature * player, int abilityID) {
	if (abilityID > 255)
	{
		return 0;
	}
	
	if (player->entity_data.classType <= 4)
	{
		return cooldownMap.at(abilityID);
	}

	int index = player->entity_data.classType - 5;
	if (index < 0 || index >= MOD->m_Classes.size())
	{
		return 0;
	}

	return MOD->m_Classes.at(index)->GetUltimateAbilityCooldown(player, abilityID);
}

__attribute__((naked)) void ASMOnGetUltimateAbilityCooldown() {
	asm(".intel_syntax \n"

		"call OnGetUltimateAbilityCooldown \n"
		"retn \n"

		".att_syntax \n"
	);
}

void InitializeOnGetUltimateCooldownHandler()
{
	WriteFarJMP(CWOffset(0x50BD0), (void*)&ASMOnGetUltimateAbilityCooldown);
	cooldownMap = std::vector<int>(256, 0);
	SetupCooldowns();
}