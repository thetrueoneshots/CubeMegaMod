#include "Creature.h"


void cube::Helper::AnnounceItem(cube::Game* game, cube::Item* item, unsigned int count, cube::Creature* creature)
{
	((void (*)(cube::Game*, cube::Item*, unsigned int, cube::Creature*))CWOffset(0x9D6F0))(game, item, count, creature);
}

void cube::Helper::LevelUp(cube::Creature* player)
{
	// Random seed
	int random = rand();

	// Create item
	cube::Item item = cube::Item(23, random % 5);
	item.modifier = random;
	cube::ItemStack stack = cube::ItemStack(1, item);

	// Insert in inventory
	//player->inventory_tabs.at(5).push_back(stack);
	// Print
	//AnnounceItem(cube::GetGame(), &item, 1, player);

	// Interaction
	cube::Interaction pickup(cube::Interaction::InteractionType::Drop);
	pickup.SetItem(item);
	player->interactions.push_back(pickup);
}