#include "Helper.h"

void cube::Helper::AnnounceItem(cube::Game* game, cube::Item* item, unsigned int count, cube::Creature* creature)
{
	((void (*)(cube::Game*, cube::Item*, unsigned int, cube::Creature*))CWOffset(0x9D6F0))(game, item, count, creature);
}

void cube::Helper::LevelUp(cube::Creature* player)
{
	// Create item
	cube::Item item = Helper::GenerateItem(ItemGenerationType::Artifact, player->entity_data.current_region);

	// Interaction
	DropItem(player, item);
}

cube::Item cube::Helper::GenerateItem(ItemGenerationType type, IntVector2 region)
{
	// Random seed
	int random = Helper::RandomInt();

	cube::Item item;
	item.modifier = 0;
	item.material = 0;
	item.formula_category = 0;
	item.num_spirits = 0;
	for (int i = 0; i < 32; i++)
	{
		item.spirits[i].material = 0;
		item.spirits[i].x = 0;
		item.spirits[i].y = 0;
		item.spirits[i].z = 0;
	}
	item.rarity = 0;
	item.region = region;
	
	switch (type)
	{
	case ItemGenerationType::Artifact:
		item.category = 23;
		item.id = random % 7;
		item.modifier = RandomInt() + region.x + region.y;
		item.rarity = 5;
		break;
	case ItemGenerationType::Pet:
		item.category = 20;
		item.id = random % 306;
		item.region = region;
		item.rarity = 4;
		break;
	case ItemGenerationType::Gear:
		item.category = 3 + random % 6;
		item.id = 0;
		if (item.category == 3)
		{
			item.id = RandomInt() % 18;
		}
		item.modifier = random;
		item.region = region;
		item.material = 1 + RandomInt() % 44;

		// Missing materials, shift material by two, to always have a correct material.
		if (item.material == 3 || item.material == 8 || item.material == 9)
		{
			item.material += 2;
		}

		item.rarity = RandomInt() % 6;
		break;
	case ItemGenerationType::Consumable:
		item.category = 1;
		item.id = 1 + RandomInt() % 14;
		item.rarity = RandomInt() % 5;
		if (item.id == 5 || item.id == 6)
		{
			item.id = 1;
		}
		break;
	case ItemGenerationType::Gold:
	default:
		item.category = 12;
		item.id = 0;
		item.material = 11;
		break;
	}

	return item;
}

void cube::Helper::DropItem(cube::Creature* creature, const cube::Item& item, int amount)
{
	cube::Interaction dropItem(cube::Interaction::InteractionType::Drop);
	dropItem.SetItem(item);
	dropItem.position = IntVector3(0, 0, 0);
	dropItem.creature_id_maybe = 0;
	dropItem.padding_probably = 0;
	dropItem.probably_padding_AC = 0;
	dropItem.field_B8 = 0;
	dropItem.field_C0 = 0;
	dropItem.field_C6 = 0;
	for (int i = 0; i < amount; i++)
	{
		creature->interactions.push_back(dropItem);
	}
}

void cube::Helper::DropItem(cube::Creature* creature, ItemGenerationType type, int amount)
{
	for (int i = 0; i < amount; i++)
	{
		DropItem(creature, GenerateItem(type, creature->entity_data.current_region));
	}
}
