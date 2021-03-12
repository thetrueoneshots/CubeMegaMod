#include "GemTraderMod.h"

int GemTraderMod::OnShopInteraction(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, int classType, long long id)
{
	if (classType == (int)cube::Enums::ClassType::GemTrader)
	{
		if (itemVector != nullptr)
		{
			if (itemVector->size() > 0)
			{
				// Set the random seed to the id of the creature to generate the same items for the same creature every time.
				

				// Add 5 potions of rarity 5
				{
					cube::Item item = cube::Item(1, 1);
					item.rarity = 4;

					int potionCount = 5;
					int sold = cube::Helper::CWGetItemsSold(game->world, item, id);

					if (sold < potionCount)
					{
						itemVector->at(0).push_back(cube::ItemStack(potionCount - sold, item));
					}
				}

				// Add 1 artifact
				{
					std::srand(id);
					cube::Item item = cube::Item(23, std::rand() % 7);
					item.region = IntVector2(std::rand(), std::rand());
					item.modifier = std::rand();
					item.rarity = 10;
					item.formula_category = std::rand();

					if (!cube::Helper::CWGetItemsSold(game->world, item, id))
					{
						itemVector->at(0).push_back(cube::ItemStack(1, item));
					}
				}
			}
		}
	}
	return 0;
}
