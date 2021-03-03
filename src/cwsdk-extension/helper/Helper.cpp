#include "Helper.h"

#define DEBUG_HELPER 0

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

void cube::Helper::LoreInteraction(cube::Creature* player, int percentage)
{
	int chance = RandomInt() % 100;
	int compare = 0;
	if (percentage < 100)
	{
		
		// percentage% (max 50%) chance for 1 star gear
		compare = min(percentage, 50);
		if (chance <= compare)
		{
			cube::Item item = GenerateItem(ItemGenerationType::Gear, player->entity_data.current_region);
			item.rarity = 0;
			DropItem(player, item);
		}
		
		// [Possible] Drop gold
	}
	else if (percentage < 150)
	{
		compare = (percentage - 100);
		// (percentage - 100)% chance of a 2-3 star weapon drop
		if (chance <= compare)
		{
			cube::Item item = GenerateItem(ItemGenerationType::Gear, player->entity_data.current_region);
			item.rarity = 1 + RandomInt() % 2;
			item.category = 3;
			item.id = RandomInt() % 18;
			DropItem(player, item);
		}
	}
	else
	{
		compare = min(percentage - 150, 100);
		// (percentage - 150) % chance of an artifact drop
		if (chance <= compare)
		{
			DropItem(player, ItemGenerationType::Artifact);
		}
	}

	if (DEBUG_HELPER)
	{
		wchar_t buffer[250];
		swprintf_s(buffer, 250, L"Lore: %d(DropChance: %d, Result: %d)\n", percentage, compare, chance);
		cube::GetGame()->PrintMessage(buffer, 250, 170, 90);
	}
	
}
