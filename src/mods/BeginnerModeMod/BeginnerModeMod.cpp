#include "BeginnerModeMod.h"

static void ApplyBeginnerBuffs(cube::Creature* creature, float* stat)
{
	if (creature->entity_data.hostility_type != (char)cube::Enums::EntityBehaviour::Hostile)
	{
		return;
	}

	int level = cube::GetGame()->GetPlayer()->entity_data.level + 1;

	if (level > 5)
	{
		return;
	}

	*stat *= (level / 6.f);
}

void BeginnerModeMod::OnCreatureArmorCalculated(cube::Creature* creature, float* armor)
{
	ApplyBeginnerBuffs(creature, armor);
}

void BeginnerModeMod::OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power)
{
	ApplyBeginnerBuffs(creature, power);
}

void BeginnerModeMod::OnCreatureSpellPowerCalculated(cube::Creature* creature, float* power)
{
	ApplyBeginnerBuffs(creature, power);
}

void BeginnerModeMod::OnCreatureHPCalculated(cube::Creature* creature, float* hp)
{
	ApplyBeginnerBuffs(creature, hp);
}

void BeginnerModeMod::OnCreatureResistanceCalculated(cube::Creature* creature, float* resistance)
{
	ApplyBeginnerBuffs(creature, resistance);
}
