#pragma once
#include "cwsdk.h"
#include "../PlayerUpdatesMod.h"

struct RaceData
{
	int race_type;
	bool gender, face, haircut, hair_color;
};

const static RaceData RACES[] = {
	{79, false, false, false, false},	// 8: Jester
	{80, false, false, true, true },	// 9: Spectrino
	{91, false, false, false, false},	//10: Raccoon
	{97, false, false, false, true},	//11: Vampire
	{165, false, true, false, true},	//12: Skeleton Knight
	{253, false, false, false, false},	//13: Archdruid
	{254, false, false, false, false},	//14: Half-demon
};

bool SetPreAppearance(cube::SaveData* saveData, cube::Creature::EntityData::Appearance* appearance)
{
	if (saveData == nullptr)
	{
		return false;
	}

	if (appearance == nullptr)
	{
		return false;
	}

	appearance->hair_color = saveData->hair_color;
	switch (saveData->race)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		return false;
		break;
	case 9:
		if (saveData->haircut > 0)
		{
			appearance->hair_model = 1489 + saveData->haircut;
		}
		return false;
		break;
	default:
		return false;
		break;
	}

	return true;
}

extern "C" void OnGenerateCreature(int* race, cube::SaveData * save_data, cube::Creature::EntityData::Appearance* appearance) {
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

		calc_race = RACES[index].race_type;
		break;
	}
	}

	*race = calc_race;

	if (SetPreAppearance(save_data, appearance))
	{
		*race = -1;
	}
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

	OnGenerateCreature(&race, &data, nullptr);

	GetRaceName(&name, race);

	std::wstring wname = std::wstring(name.begin(), name.end());

	((void (*)(void*, const wchar_t*))CWOffset(0x486B0))(toAppend, wname.c_str());
}

extern "C" void OnGetGenderText(void* toAppend, cube::CharacterStyleWidget * widget)
{
	std::string name = "Male";
	if (widget->gender == 1)
	{
		name = "Female";
	}

	if (widget->race > 7)
	{
		int index = widget->race - 8;
		if (!RACES[index].gender)
		{
			name = "<None>";
		}
	}

	((void (*)(void*, const char*))CWOffset(0x6D8E0))(toAppend, name.c_str());
}

extern "C" void OnGetFaceText(void* toAppend, cube::CharacterStyleWidget * widget)
{
	std::wstring name = L"Face " + std::to_wstring(widget->face + 1);

	if (widget->race > 7)
	{
		int index = widget->race - 8;
		if (!RACES[index].face)
		{
			name = L"<None>";
		}
	}

	((void (*)(void*, const wchar_t*))CWOffset(0x486B0))(toAppend, name.c_str());
}

extern "C" void OnGetHairCutText(void* toAppend, cube::CharacterStyleWidget * widget)
{
	std::wstring name = L"Haircut " + std::to_wstring(widget->haircut + 1);

	if (widget->race > 7)
	{
		int index = widget->race - 8;
		if (!RACES[index].haircut)
		{
			name = L"<None>";
		}
	}

	((void (*)(void*, const wchar_t*))CWOffset(0x486B0))(toAppend, name.c_str());
}

extern "C" void OnGetHairColorText(void* toAppend, cube::CharacterStyleWidget * widget)
{
	std::wstring name = L"Hair color";

	if (widget->race > 7)
	{
		int index = widget->race - 8;
		RaceData data = RACES[index];
		if (data.hair_color && !data.haircut)
		{
			name = L"Eye color";
		}

		if (!data.hair_color)
		{
			name = L"";
		}
	}

	((void (*)(void*, const wchar_t*))CWOffset(0x486B0))(toAppend, name.c_str());
}

extern "C" int OnGetHairColorDisplay(cube::CharacterStyleWidget * widget)
{
	if (widget->race > 7)
	{
		int index = widget->race - 8;

		if (!RACES[index].hair_color)
		{
			return 0;
		}
	}

	widget->preview_hair_color = widget->current_hair_color;
	return 1;
}

GETTER_VAR(void*, ASMOnDrawColorPicker_jmpback);
GETTER_VAR(void*, ASMOnDrawColorPicker_bail);
__attribute__((naked)) void ASMOnDrawColorPicker() {
	asm(".intel_syntax \n"
		// Set parameters
		"mov rcx, rdi \n"	// cube::CharacterStyleWidget* widget

		// Call function
		PREPARE_STACK
		"call OnGetHairColorDisplay \n"
		RESTORE_STACK

		"xorps xmm0, xmm0 \n"
		"movdqu [rbp + 0x58], xmm0 \n"
		"mov [rbp + 0x68], rsi \n"

		"cmp rax, 1 \n"
		"jne 1f \n"

		DEREF_JMP(ASMOnDrawColorPicker_jmpback)

		"1: \n"
		DEREF_JMP(ASMOnDrawColorPicker_bail)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMOnDrawHairColor_jmpback);
__attribute__((naked)) void ASMOnDrawHairColor() {
	asm(".intel_syntax \n"
		// Set parameters
		"lea rcx, [rsp + 0x50] \n"	// void* toAppend
		"mov rdx, rdi \n"			// cube::CharacterStyleWidget* widget

		// Call function
		PREPARE_STACK
		"call OnGetHairColorText \n"
		RESTORE_STACK

		DEREF_JMP(ASMOnDrawHairColor_jmpback)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMOnDrawHairCut_jmpback);
__attribute__((naked)) void ASMOnDrawHairCut() {
	asm(".intel_syntax \n"
		// Set parameters
		"lea rcx, [rsp + 0x50] \n"	// void* toAppend
		"mov rdx, rdi \n"			// cube::CharacterStyleWidget* widget

		// Call function
		PREPARE_STACK
		"call OnGetHairCutText \n"
		RESTORE_STACK

		DEREF_JMP(ASMOnDrawHairCut_jmpback)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMOnDrawFace_jmpback);
__attribute__((naked)) void ASMOnDrawFace() {
	asm(".intel_syntax \n"
		// Set parameters
		"lea rcx, [rsp + 0x50] \n"	// void* toAppend
		"mov rdx, rdi \n"			// cube::CharacterStyleWidget* widget

		// Call function
		PREPARE_STACK
		"call OnGetFaceText \n"
		RESTORE_STACK

		DEREF_JMP(ASMOnDrawFace_jmpback)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMOnDrawGender_jmpback);
__attribute__((naked)) void ASMOnDrawGender() {
	asm(".intel_syntax \n"
		// Set parameters
		"lea rcx, [rsp + 0x50] \n"	// void* toAppend
		"mov rdx, rdi \n"			// cube::CharacterStyleWidget* widget

		// Call function
		PREPARE_STACK
		"call OnGetGenderText \n"
		RESTORE_STACK

		DEREF_JMP(ASMOnDrawGender_jmpback)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMOnGenerateCreature_jmpback);
__attribute__((naked)) void ASMOnGenerateCreature() {
	asm(".intel_syntax \n"

		// Save registers
		PUSH_ALL

		// Set parameters
		"mov rcx, r12 \n"
		"mov rdx, r8 \n"
		"mov r8, rbx \n"

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

	WriteFarJMP(CWOffset(0x27135A), ASMOnDrawGender);
	ASMOnDrawGender_jmpback = CWOffset(0x27137B);

	WriteFarJMP(CWOffset(0x271640), ASMOnDrawFace);
	ASMOnDrawFace_jmpback = CWOffset(0x271663);

	WriteFarJMP(CWOffset(0x2717A3), ASMOnDrawHairCut);
	ASMOnDrawHairCut_jmpback = CWOffset(0x2717C6);

	WriteFarJMP(CWOffset(0x271D2A), ASMOnDrawHairColor);
	ASMOnDrawHairColor_jmpback = CWOffset(0x271D3B);

	WriteFarJMP(CWOffset(0x271DC2), ASMOnDrawColorPicker);
	ASMOnDrawColorPicker_jmpback = CWOffset(0x271DE6);
	ASMOnDrawColorPicker_bail = CWOffset(0x272326);

	auto offset_increase = 0x272648;
	auto offset_decrease = 0x2725F1;

	WriteByte(CWOffset(offset_increase + 0x02), 7 + sizeof(RACES) / sizeof(RACES[0]));
	WriteByte(CWOffset(offset_decrease + 0x01), 7 + sizeof(RACES) / sizeof(RACES[0]));
}