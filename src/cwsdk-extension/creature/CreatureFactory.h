#pragma once

namespace cube
{
	class Creature;

	enum CreatureType
	{
		CreatureTypeBlueFish = 0,
		CreatureTypeYellowFish,
		CreatureTypeShark,
		CreatureTypeBigBlueFish,
		CreatureTypeMawFish,
		CreatureTypeBlobFish,
		CreatureTypeSeaHorse,
	};

	class CreatureFactory
	{
	public:
		static cube::Creature* CreateCreature(CreatureType type, int level);
		static void AddCreatureToWorld(cube::Creature* creature);
	};
}