/*
* Hook for executing abilities.
*/
#pragma once

#include "cwsdk.h"
#include "../PlayerUpdatesMod.h"

#include "../abilities/FullHealAbility.h"
#include "../abilities/HealingPuddle.h"
#include "../abilities/LavaPuddle.h"
#include "../abilities/PoisonPuddle.h"

void AnimationTest(cube::World* world, cube::Creature* player);

extern "C" void OnExecuteAbility(cube::World* world, cube::Creature* player) {
	if (player->entity_data.classType <= 4 || player->entity_data.current_ability <= 165)
	{
		return;
	}

	switch (player->entity_data.current_ability)
	{
	case CharacterClass::Ability::FullHeal:
		cube::GetGame()->PrintMessage(L"Execute Bulwark full heal!");
		ExecuteFullHealAbility(player, true);
		break;
	case CharacterClass::Ability::PuddleHeal:
		ExecuteSelfHealingPuddleAbility(world, player);
		player->entity_data.hit_combo += 20;
		player->entity_data.time_since_hit = 0;
		break;
	case CharacterClass::Ability::PuddleLava:
		player->entity_data.current_ability = 0;
		if (player->entity_data.MP >= 0.2f)
		{
			ExecuteSelfLavaPuddleAbility(world, player);
			player->entity_data.MP -= 0.1f;
			player->entity_data.hit_combo += 1;
			player->entity_data.time_since_hit = 0;
		}
		break;
	case CharacterClass::Ability::PuddlePoison:
		player->entity_data.current_ability = 0;
		if (player->stamina >= 0.5)
		{
			ExecuteSelfPoisonPuddleAbility(world, player);
			player->stamina -= 0.5f;
			player->entity_data.hit_combo += 5;
			player->entity_data.time_since_hit = 0;
		}
		break;
	case CharacterClass::Ability::AnimationTest:
		AnimationTest(world, player);
		break;
	default:
		break;
	}
}

void AnimationTest(cube::World* world, cube::Creature* player)
{
	float time = player->entity_data.time_since_ability;
	int max_time = 500.f;

	if (time > max_time)
	{
		player->entity_data.current_ability = 0;
	}

	player->entity_data.appearance.chest_rotation = (time / max_time) * 360.f;
}

GETTER_VAR(void*, ASMOnExecuteAbility_jmpback);
GETTER_VAR(void*, ASMOnExecuteAbility_jmpback_2);
//GETTER_VAR(void*, ASMOnCanEquipItem_bail);
__attribute__((naked)) void ASMOnExecuteAbility() {
	asm(".intel_syntax \n"
		"mov rax, rsp \n"
		"sub rsp, 0x110 \n"
		"movaps xmmword ptr [rax - 0x10], xmm0 \n"
		"movaps xmmword ptr [rax - 0x20], xmm1 \n"
		"movaps xmmword ptr [rax - 0x30], xmm2 \n"
		"movaps xmmword ptr [rax - 0x40], xmm3 \n"
		"movaps xmmword ptr [rax - 0x50], xmm4 \n"
		"movaps xmmword ptr [rax - 0x60], xmm5 \n"
		"movaps xmmword ptr [rax - 0x70], xmm6 \n"
		"movaps xmmword ptr [rax - 0x80], xmm7 \n"
		"movaps xmmword ptr [rax - 0x90], xmm8 \n"
		"movaps xmmword ptr [rax - 0xA0], xmm9 \n"
		"movaps xmmword ptr [rax - 0xB0], xmm10 \n"
		"movaps xmmword ptr [rax - 0xC0], xmm11 \n"
		"movaps xmmword ptr [rax - 0xD0], xmm12 \n"
		"movaps xmmword ptr [rax - 0xE0], xmm13 \n"
		"movaps xmmword ptr [rax - 0xF0], xmm14 \n"
		"movaps xmmword ptr [rax - 0x100], xmm15 \n"
		PUSH_ALL
		"mov rdx, r13 \n"
		"mov rcx, r15 \n"
		PREPARE_STACK
		"call OnExecuteAbility \n"
		RESTORE_STACK
		POP_ALL
		"movaps xmm0, xmmword ptr [rax - 0x10] \n"
		"movaps xmm1, xmmword ptr [rax - 0x20] \n"
		"movaps xmm2, xmmword ptr [rax - 0x30] \n"
		"movaps xmm3, xmmword ptr [rax - 0x40] \n"
		"movaps xmm4, xmmword ptr [rax - 0x50] \n"
		"movaps xmm5, xmmword ptr [rax - 0x60] \n"
		"movaps xmm6, xmmword ptr [rax - 0x70] \n"
		"movaps xmm7, xmmword ptr [rax - 0x80] \n"
		"movaps xmm8, xmmword ptr [rax - 0x90] \n"
		"movaps xmm9, xmmword ptr [rax - 0xA0] \n"
		"movaps xmm10, xmmword ptr [rax - 0xB0] \n"
		"movaps xmm11, xmmword ptr [rax - 0xC0] \n"
		"movaps xmm12, xmmword ptr [rax - 0xD0] \n"
		"movaps xmm13, xmmword ptr [rax - 0xE0] \n"
		"movaps xmm14, xmmword ptr [rax - 0xF0] \n"
		"movaps xmm15, xmmword ptr [rax - 0x100] \n"
		"add rsp, 0x110 \n"
		
		// Original code
		"xorps xmm15, xmm15 \n"
		"cmp byte ptr[r13 + 0x68], 0x85 \n"
		"jnz 1f \n"
		"movss xmm0, dword ptr[r13 + 0x44] \n"
		DEREF_JMP(ASMOnExecuteAbility_jmpback)

		"1: \n"
		DEREF_JMP(ASMOnExecuteAbility_jmpback_2)

		".att_syntax \n"
	);
}

void InitializeOnExecuteAbilityHandler()
{
	WriteFarJMP(CWOffset(0x2BBAB2), (void*)&ASMOnExecuteAbility);
	ASMOnExecuteAbility_jmpback = CWOffset(0x2BBAC3);
	ASMOnExecuteAbility_jmpback_2 = CWOffset(0x2BBAF4);
	// Todo: Bail
	//ASMOnExecuteAbility_bail = CWOffset(0x109677);
}