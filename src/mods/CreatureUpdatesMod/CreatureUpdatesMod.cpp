#include "CreatureUpdatesMod.h"

static void BuffPet(cube::Creature* creature, float* stat)
{
	if (creature->entity_data.hostility_type == (char)cube::Enums::EntityBehaviour::Pet)
	{
		*stat *= 2.f;
	}
}

void CreatureUpdatesMod::Initialize()
{
	auto offset = 0x83590;
	int data[] = {
		0xB8,
		0x28,
		0x00,
		0x00,
		0x00,
		0x90,
	};

	int cnt = sizeof(data) / sizeof(*data);
	for (int i = 0; i < cnt; i++)
	{
		WriteByte(CWOffset(offset + i), data[i]);
	}
}

void CreatureUpdatesMod::OnCreatureArmorCalculated(cube::Creature* creature, float* armor)
{
	BuffPet(creature, armor);
}

void CreatureUpdatesMod::OnCreatureCriticalCalculated(cube::Creature* creature, float* critical)
{
	BuffPet(creature, critical);
}

void CreatureUpdatesMod::OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power)
{
	if (creature->entity_data.classType == (int)cube::Enums::ClassType::Ranger &&
		creature->entity_data.hostility_type == (int)cube::Enums::EntityBehaviour::Hostile)
	{
		if (creature->entity_data.equipment.weapon_right.id == 8 ||
			creature->entity_data.equipment.weapon_left.id == 8)
		{
			*power *= 0.5f;
		}
	}

	BuffPet(creature, power);
}

void CreatureUpdatesMod::OnCreatureSpellPowerCalculated(cube::Creature* creature, float* power)
{
	if (creature->entity_data.classType == (int)cube::Enums::ClassType::Mage &&
		creature->entity_data.hostility_type == (int)cube::Enums::EntityBehaviour::Hostile)
	{
		*power *= 0.5f;
	}

	BuffPet(creature, power);
}

void CreatureUpdatesMod::OnCreatureHasteCalculated(cube::Creature* creature, float* haste)
{
	BuffPet(creature, haste);
}

void CreatureUpdatesMod::OnCreatureHPCalculated(cube::Creature* creature, float* hp)
{
	BuffPet(creature, hp);
}

void CreatureUpdatesMod::OnCreatureResistanceCalculated(cube::Creature* creature, float* resistance)
{
	BuffPet(creature, resistance);
}

void CreatureUpdatesMod::OnCreatureRegenerationCalculated(cube::Creature* creature, float* regeneration)
{
	BuffPet(creature, regeneration);
}

void CreatureUpdatesMod::OnCreatureManaGenerationCalculated(cube::Creature* creature, float* manaGeneration)
{
	BuffPet(creature, manaGeneration);
}
