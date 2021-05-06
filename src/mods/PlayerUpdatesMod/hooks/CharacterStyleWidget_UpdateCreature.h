#pragma once
#include "cwsdk.h"

extern "C" void CharacterStyleWidgetUpdateCreature(cube::CharacterStyleWidget * this) {

}

__attribute__((naked)) void ASMCharacterStyleWidgetUpdateCreature() {
	asm(".intel_syntax \n"

		"retn \n"
		".att_syntax \n"
	);
}

void InitializeCharacterStyleWidgetUpdateCreatureHandler() {
	WriteFarJMP(CWOffset(0x272D90), (void*)&ASMCharacterStyleWidgetUpdateCreature);
}