#pragma once
#include "cwsdk.h"
#include "../PlayerUpdatesMod.h"

const static int RACES[] = {
	79,
	80,
	91,
	97,
	165,
};

extern "C" void OnGenerateCreature(int* race, cube::SaveData * save_data) {
	int gender = save_data->gender;
	int calc_race = 0;

	switch (save_data->race)
	{
	case 0:
		calc_race = (gender & 1) + 2;
		break;
	case 1:
		calc_race = gender & 1;
		break;
	case 2:
		calc_race = (gender & 1) + 9;
		break;
	case 3:
		calc_race = (gender & 1) + 11;
		break;
	case 4:
		calc_race = (gender & 1) + 4;
		break;
	case 5:
		calc_race = (gender & 1) + 7;
		break;
	case 6:
		calc_race = (gender & 1) + 15;
		break;
	case 7:
		calc_race = (gender & 1) + 13;
		break;
	default:
	{
		int index = save_data->race - 8;
		int size = sizeof(RACES) / sizeof(RACES[0]);

		if (index >= size) {
			break;
		}

		calc_race = RACES[index];
		break;
	}
	}

	*race = calc_race;
}

std::string* GetRaceName(std::string* string, int race)
{
	switch (race)
	{
	case 2:
	case 3:
		*string = "Human";
		break;
	case 0:
	case 1:
		*string = "Elf";
		break;
	case 11:
	case 12:
		*string = "Orc";
		break;
	case 9:
	case 10:
		*string = "Dwarf";
		break;
	case 4:
	case 5:
		*string = "Goblin";
		break;
	case 7:
	case 8:
		*string = "Lizard";
		break;
	case 15:
	case 16:
		*string = "Undead";
		break;
	case 13:
	case 14:
		*string = "Frog";
		break;
	case 95:
		*string = "Santa";
		break;
	case 83:
	case 84:
		*string = "Nomad";
		break;
	default:
	{
		cube::Game* game = cube::GetGame();
		if (game != nullptr)
		{
			auto res = game->speech.entity_type_id_map.find(race);
			if (res != game->speech.entity_type_id_map.end())
			{
				std::wstring* wstr = &res->second;
				std::string str = std::string(wstr->begin(), wstr->end());
				*string = str;
			}
		}
	}
	break;
	}
	return string;
}

extern "C" void OnGetRaceName(void* toAppend, cube::Creature* creature)
{
	if (creature == nullptr)
	{
		return;
	}

	std::string name;

	GetRaceName(&name, creature->entity_data.race);
	
	((void (*)(void*, const char*))CWOffset(0x6D8E0))(toAppend, name.c_str());
}

extern "C" void OnGetRaceName2(void* toAppend, int raceIndex)
{
	std::string name;

	int race;

	cube::SaveData data;
	data.race = raceIndex;
	data.gender = 0;

	OnGenerateCreature(&race, &data);

	GetRaceName(&name, race);

	std::wstring wname = std::wstring(name.begin(), name.end());

	((void (*)(void*, const wchar_t*))CWOffset(0x486B0))(toAppend, wname.c_str());
}



GETTER_VAR(void*, ASMOnGenerateCreature_jmpback);
__attribute__((naked)) void ASMOnGenerateCreature() {
	asm(".intel_syntax \n"

		// Save registers
		PUSH_ALL

		// Set parameters
		"mov rcx, r12 \n"
		"mov rdx, r8 \n"

		// Call function
		PREPARE_STACK
		"call OnGenerateCreature \n"
		RESTORE_STACK

		// Restore registers
		POP_ALL

		DEREF_JMP(ASMOnGenerateCreature_jmpback)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMOnGetRaceName_jmpback);
__attribute__((naked)) void ASMOnGetRaceName() {
	asm(".intel_syntax \n"

		// Set parameters
		"lea rcx, [rsp + 0x50] \n"
		"mov rdx, rax \n"

		// Call function
		PREPARE_STACK
		"call OnGetRaceName \n"
		RESTORE_STACK

		DEREF_JMP(ASMOnGetRaceName_jmpback)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMOnGetRaceName2_jmpback);
__attribute__((naked)) void ASMOnGetRaceName2() {
	asm(".intel_syntax \n"

		// Set parameters
		"lea rcx, [rsp + 0x50] \n"
		"mov rdx, rax \n"

		// Call function
		PREPARE_STACK
		"call OnGetRaceName2 \n"
		RESTORE_STACK

		DEREF_JMP(ASMOnGetRaceName2_jmpback)
		".att_syntax \n"
	);
}

void InitializeOnGenerateCreatureHandler() {
	WriteFarJMP(CWOffset(0x53FDB), (void*)&ASMOnGenerateCreature);
	ASMOnGenerateCreature_jmpback = CWOffset(0x54057);


	WriteFarJMP(CWOffset(0x26F548), (void*)&ASMOnGetRaceName);
	ASMOnGetRaceName_jmpback = CWOffset(0x26F5A4);

	WriteFarJMP(CWOffset(0x271144), (void*)&ASMOnGetRaceName2);
	ASMOnGetRaceName2_jmpback = CWOffset(0x2711A5);

	auto offset_increase = 0x272648;
	auto offset_decrease = 0x2725F1;

	WriteByte(CWOffset(offset_increase + 0x02), 7 + sizeof(RACES) / sizeof(RACES[0]));
	WriteByte(CWOffset(offset_decrease + 0x01), 7 + sizeof(RACES) / sizeof(RACES[0]));
}