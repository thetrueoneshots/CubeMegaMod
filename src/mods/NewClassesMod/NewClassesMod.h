#pragma once
#include "../../CubeMod.h"
#include "CharacterClass.h"

class NewClassesMod : public CubeMod
{
public:
	std::vector<CharacterClass*> m_Classes;

	NewClassesMod() {
		m_Name = "New Classes Mod";
		m_FileName = "NewClassesMod";
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