#pragma once

static cube::Creature* s_DropCreature;

// Calculates the value of coins based on your level and a seed
// Note: Currently clamped from (0 - 2^8)
int CalculateCoinValue(int level, int seed)
{
	int value = 1 * (1 + level) + seed % 2;
	return value > 0xFFFF ? 0xFFFF : value;
}

extern "C" void DropGold(cube::Creature* p1, void* p2) {
	int seed = rand();
	int random = seed % 1;

	if (random != 0)
	{
		return;
	}

	// Set position of the gold dropping invisble creature to the hit creature
	s_DropCreature->entity_data.position = p1->entity_data.position;

	// Calculate coin value
	int value = CalculateCoinValue(p1->entity_data.level, seed);

	// Disable gear drops
	WriteByte((char*)CWBase() + 0x2A71DB + 0x04, 0);
	// Disable special drops
	WriteByte((char*)CWBase() + 0x2A7360 + 0x04, 0);
	// Set the value of a gold coin
	WriteByte((char*)CWBase() + 0x2A7602 + 0x04, value & 0xFF);
	WriteByte((char*)CWBase() + 0x2A7602 + 0x05, (value >> 0x08) & 0xFF);

	// Drop loot
	((void (*)(void*, cube::Creature*))CWOffset(0x2A6860))(p2, s_DropCreature);

	// Reset the drops
	WriteByte((char*)CWBase() + 0x2A71DB + 0x04, 1);
	WriteByte((char*)CWBase() + 0x2A7360 + 0x04, 1);
	WriteByte((char*)CWBase() + 0x2A7602 + 0x04, 1);
}

GETTER_VAR(void*, ASMDropGoldOnHit_jmpback);
GETTER_VAR(void*, ASMDropGoldOnHit_bail);
__attribute__((naked)) void ASMDropGoldOnHit() {
	asm(".intel_syntax \n"
		"mov r14, [rsp+0x20] \n"
		PUSH_ALL
		"mov rdx, r14 \n"
		"mov rcx, r13 \n"

		PREPARE_STACK

		"call DropGold \n"

		RESTORE_STACK

		POP_ALL

		"comiss xmm9, [r13+0x180] \n"
		"jb 1f \n"

		DEREF_JMP(ASMDropGoldOnHit_jmpback)

		"1: \n"
		DEREF_JMP(ASMDropGoldOnHit_bail)
		".att_syntax \n"
		);
}

void SetupDropGoldOnHitHandler() {
	// Setup asm hook
	char* base = (char*)CWBase();
	WriteFarJMP(base + 0x29E486, (void*)&ASMDropGoldOnHit);
	ASMDropGoldOnHit_jmpback = (void*)(base + 0x29E494);
	ASMDropGoldOnHit_bail = (void*)(base + 0x29EB1C);
}

void DropGoldOnHitInitialize()
{
	SetupDropGoldOnHitHandler();

	s_DropCreature = cube::Creature::Create(0);

	if (s_DropCreature == nullptr) {
		Popup("Mod error", "Failed to create creature for dropping gold.");
		return;
	}

	s_DropCreature->entity_data.race = 0; // Set the race to elf (something basic)
	s_DropCreature->entity_data.hostility_type = 1; // Set the hostility type to hostile
	s_DropCreature->entity_data.level = 0; // Set the level to 0 (not sure if that influences drops)

	// Allow everything to drop gold
	WriteByte((char*)CWBase() + 0x2A74D3 + 0x01, 0x80);
}