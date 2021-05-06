#pragma once
#include "../../CubeMod.h"
#include "CharacterClass.h"

class PlayerUpdatesMod : public CubeMod
{
public:
	std::vector<CharacterClass*> m_Classes;

	PlayerUpdatesMod() {
		m_Name = "Player Updates Mod";
		m_FileName = "PlayerUpdatesMod";
		m_ID = 11;
		m_Version = { 1, 0, 0 };
	}

	void OnGameTick(cube::Game* game);
	void Initialize();
};

/*
* Idea for classes
* # CharacterClass
	unsigned char ID;
	std::wstring name;
	std::wstring spec1;
	std::Wstring spec2;
	
	void OnUltUsage(int *abilityID);
	void OnGetUltCooldown(int abilityID, int* cooldown);
	void OnShiftUsage(int *abilityID);
	void OnMiddleMouseUsage(int *ability);
	bool OnCanEquipItem(cube::Item* item);
	void OnLoadAppearance(cube::Creature* creature);
	void OnCharacterCreation(cube::Creature* creature);
*/