#include "Creature.h"
#include "../cwsdk.h"

cube::Creature* cube::Creature::Create(__int64 id) {
    cube::Creature* newCreature = (cube::Creature*)new char[sizeof(cube::Creature)];
    newCreature->ctor(&id);
    return newCreature;
}

cube::Creature* cube::Creature::ctor(__int64* id) {
    return ((cube::Creature*(*)(cube::Creature*, __int64*))CWOffset(0x4CE80))(this, id);
}

float cube::Creature::GetArmor() {
	return ((float (*)(cube::Creature*))CWOffset(0x4F080))(this);
}

float cube::Creature::GetCritical(cube::Creature* other_creature, bool other_creature_based_on_resistance) {
	return ((float (*)(cube::Creature*, cube::Creature*, bool))CWOffset(0x50D30))(this, other_creature, other_creature_based_on_resistance);
}

float cube::Creature::GetAttackPower(bool unk_bool) {
	return ((float (*)(cube::Creature*, bool))CWOffset(0x4FA70))(this, unk_bool);
}

float cube::Creature::GetSpellPower(bool unk_bool) {
	return ((float (*)(cube::Creature*, bool))CWOffset(0x65C70))(this, unk_bool);
}

float cube::Creature::GetHaste() {
	return ((float (*)(cube::Creature*))CWOffset(0x66460))(this);
}

float cube::Creature::GetMaxHP() {
	return ((float (*)(cube::Creature*))CWOffset(0x5FAC0))(this);
}

float cube::Creature::GetResistance() {
	return ((float (*)(cube::Creature*))CWOffset(0x64D90))(this);
}

float cube::Creature::GetRegeneration() {
	return ((float (*)(cube::Creature*))CWOffset(0x647B0))(this);
}

float cube::Creature::GetManaGeneration() {
	return ((float (*)(cube::Creature*))CWOffset(0x5F8D0))(this);
}
