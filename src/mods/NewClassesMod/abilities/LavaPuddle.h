#include "cwsdk.h"

inline void ExecuteSelfLavaPuddleAbility(cube::World* world, cube::Creature* creature)
{
	creature->entity_data.current_ability = 116;
	creature->entity_data.time_since_ability = 0;
	cube::Projectile puddle(creature->entity_data.position, cube::Projectile::ProjectileType::Puddle, cube::Projectile::ProjectileSubType::LavaPuddle, 1000);
	puddle.guid = creature->id;
	puddle.damage = creature->GetAttackPower();
	world->projectiles.push_front(puddle);
}