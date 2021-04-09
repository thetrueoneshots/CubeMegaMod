#pragma once
#include <string>
#include "cwsdk.h"

class CharacterClass
{
public:
	char* m_Name;
	wchar_t* m_WideName;

	CharacterClass(char* name, wchar_t* widename) : m_Name(name), m_WideName(widename) {};
	~CharacterClass() {};
	
	// Careful with floats. Printing in the chat causes a crash, because xmm registers are changed when using floats.

	inline virtual void GenerateStarterGear(cube::Game* game, cube::Creature* player) {}
	inline virtual int GetUltimateAbilityId(cube::Creature* player) { return 0; }
	inline virtual int GetUltimateAbilityCooldown(cube::Creature* player, int abilityID) { return 0; }
	inline virtual int GetShiftAbilityId(cube::Creature* player) { return 0; }
	inline virtual int GetMiddleMouseAbilityId(cube::Creature * player) { return 0; }
	inline virtual bool CanEquipItem(cube::Item* item) { return true; }

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