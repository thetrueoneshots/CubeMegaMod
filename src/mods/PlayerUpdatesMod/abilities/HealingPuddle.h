#include "cwsdk.h"

inline void ExecuteSelfHealingPuddleAbility(cube::World* world, cube::Creature* creature)
{
	creature->entity_data.current_ability = 116;
	creature->entity_data.time_since_ability = 0;
	cube::Projectile healpuddle(creature->entity_data.position, cube::Projectile::ProjectileType::Medicine, cube::Projectile::ProjectileSubType::HealingMedicine, 10000);
	healpuddle.guid = creature->id;
	healpuddle.damage = creature->GetAttackPower();
	world->projectiles.push_front(healpuddle);
}