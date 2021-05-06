#pragma once
#include "cwsdk.h"
#include "../../../hooks.h"
#include "../PlayerUpdatesMod.h"

const static int STANDARD_CLASS_COUNT = 4;

static char* CLASSNAME_ROGUE = "Rogue";
static wchar_t* CLASSNAME_ROGUE_WIDE = L"Rogue";

/*
* GET CLASS NAME WCHAR_T*
*/

// Note: ID is 0 at rogue, so 1 at the first new class
extern "C" wchar_t* GetCubeClassNameWide(int id) {
	int index = id - 1;
	if (index < 0 || index >= MOD->m_Classes.size())
	{
		return CLASSNAME_ROGUE_WIDE;
	}

	return MOD->m_Classes.at(index)->m_WideName;
}

GETTER_VAR(void*, ASMSetMenuClassName_retn);
__attribute__((naked)) void ASMSetMenuClassName() {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"push rax \n"
		"call GetCubeClassNameWide \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetMenuClassName_retn)
		".att_syntax \n"
	);
}

/*
* GET CLASS NAME CHAR*
*/

// Note: ID is 0 at rogue, so 1 at the first new class
extern "C" char* GetCubeClassName(int id) {
	int index = id - 1;
	if (index < 0 || index >= MOD->m_Classes.size())
	{
		return CLASSNAME_ROGUE;
	}

	return MOD->m_Classes.at(index)->m_Name;
}

GETTER_VAR(void*, ASMSetClassName_1_ret);
__attribute__((naked)) void ASMSetClassName_1() {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"push rax \n"
		"call GetCubeClassName \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_1_ret)
	);
}

GETTER_VAR(void*, ASMSetClassName_2_ret);
__attribute__((naked)) void ASMSetClassName_2() {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"push rax \n"
		"call GetCubeClassName \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_2_ret)
		".att_syntax \n"
	);
}

/*
* CHARACTER WIDGET CLASS ID INCREASE
*/

extern "C" void OnCharacterWidgetClassButtonIncrease(cube::CharacterStyleWidget * widget) {
	widget->class_type++;
	if (widget->class_type >= STANDARD_CLASS_COUNT + MOD->m_Classes.size())
	{
		widget->class_type = 0;
	}
}

GETTER_VAR(void*, OverwriteClassIdIncrease_ret);
__attribute__((naked)) void ASMMenuClassIdIncrease() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, rbx \n"
		PREPARE_STACK
		"call OnCharacterWidgetClassButtonIncrease \n"
		RESTORE_STACK
		POP_ALL
		// Old code
		"xor edx, edx \n"
		"mov rcx, rbx \n"
		DEREF_JMP(OverwriteClassIdIncrease_ret)
		".att_syntax \n"
	);
}

/*
* CHARACTER WIDGET CLASS ID DECREASE
*/

extern "C" void OnCharacterWidgetClassButtonDecrease(cube::CharacterStyleWidget * widget) {
	widget->class_type--;
	if (widget->class_type < 0)
	{
		widget->class_type = STANDARD_CLASS_COUNT + MOD->m_Classes.size() - 1;
	}
}

GETTER_VAR(void*, OverwriteClassIdDecrease_ret);
__attribute__((naked)) void ASMMenuClassIdDecrease() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, rbx \n"
		PREPARE_STACK
		"call OnCharacterWidgetClassButtonDecrease \n"
		RESTORE_STACK
		POP_ALL
		// Old code
		"xor edx, edx \n"
		"mov rcx, rbx \n"
		DEREF_JMP(OverwriteClassIdDecrease_ret)
		".att_syntax \n"
	);
}

/*
* CHARACTER GENERATE STARTER GEAR
*/

extern "C" char GenerateStarterGear(cube::Game * game) {
	cube::Creature* player = game->GetPlayer();

	// Do the normal things for the standar classes.
	if (player->entity_data.classType <= STANDARD_CLASS_COUNT)
	{
		return game->GeneratePlayerStarterGear();
	}

	int index = player->entity_data.classType - STANDARD_CLASS_COUNT - 1;
	if (index < 0 || index >= MOD->m_Classes.size())
	{
		return 0;
	}

	player->ClearInventoryGear();
	player->entity_data.equipment.Clear();
	MOD->m_Classes.at(index)->GenerateStarterGear(game, player);
	return 0;
}

GETTER_VAR(void*, AddCreatureStarterWeapons_ret);
__attribute__((naked)) void ASMAddCreatureStarterWeapons() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rcx, [rdi + 0x1E8] \n"
		PREPARE_STACK
		"call GenerateStarterGear \n"
		RESTORE_STACK
		POP_ALL
		"mov rcx, [rdi + 0x1E8] \n"
		"mov rcx, [rcx + 0x08] \n"
		DEREF_JMP(AddCreatureStarterWeapons_ret)
		".att_syntax \n"
	);
}

void AddMenuClassNames() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x2714CF, (void*)&ASMSetMenuClassName);
	ASMSetMenuClassName_retn = (base + 0x2714F6);
}

void AddClassNames() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x27405A, (void*)&ASMSetClassName_1);
	ASMSetClassName_1_ret = (base + 0x274081);
	WriteFarJMP(base + 0x26F5D2, (void*)&ASMSetClassName_2);
	ASMSetClassName_2_ret = (base + 0x26F5F9);
}

void OverwriteClassIdIncrease() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x27243A, (void*)&ASMMenuClassIdIncrease);
	OverwriteClassIdIncrease_ret = (base + 0x272459);
}

void OverwriteClassIdDecrease() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x2723EA, (void*)&ASMMenuClassIdDecrease);
	OverwriteClassIdDecrease_ret = (base + 0x27240A);
}

void AddCreatureStarterWeapons() {
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x273176, (void*)&ASMAddCreatureStarterWeapons);
	AddCreatureStarterWeapons_ret = (base + 0x27318D);
}

void InitializeMenuHook() {
	AddMenuClassNames();
	AddClassNames();
	OverwriteClassIdIncrease();
	OverwriteClassIdDecrease();
	AddCreatureStarterWeapons();
}