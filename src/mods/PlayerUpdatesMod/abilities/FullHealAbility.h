#include "cwsdk.h"

inline void ExecuteFullHealAbility(cube::Creature* creature, bool activate_when_dead = false)
{
	if (!creature)
	{
		return;
	}

	if (activate_when_dead || creature->entity_data.HP > 0)
	{
		creature->entity_data.HP = creature->GetMaxHP();
	}
	creature->entity_data.current_ability = 0;
}