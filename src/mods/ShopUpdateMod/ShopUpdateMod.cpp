#include "ShopUpdateMod.h"

static void UpdateGemTraderShop(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, long long id);
static void UpdateItemVendorShop(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, long long id);
static void UpdateWeaponVendorShop(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, long long id);

int ShopUpdateMod::OnShopInteraction(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, int classType, long long id)
{
	if (itemVector != nullptr)
	{
		if (itemVector->size() > 0)
		{
			switch (classType)
			{
			case (int)cube::Enums::ClassType::GemTrader:
				UpdateGemTraderShop(game, itemVector, id);
				break;
			case (int)cube::Enums::ClassType::ItemVendor:
				UpdateItemVendorShop(game, itemVector, id);
				break;
			case (int)cube::Enums::ClassType::WeaponVendor:
				UpdateWeaponVendorShop(game, itemVector, id);
				break;
			default:
				break;
			}
		}
	}
	return 0;
}

static void UpdateGemTraderShop(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, long long id)
{
	// Add 3 potions of rarity 1 - 4
	for (int i = 0; i < 4; i++)
	{
		cube::Item item = cube::Item(1, 1);
		item.rarity = i;

		int potionCount = 3;
		int sold = cube::Helper::CWGetItemsSold(game->world, item, id);

		if (sold < potionCount)
		{
			itemVector->at(0).push_back(cube::ItemStack(potionCount - sold, item));
		}
	}

	// Add 1 artifact
	{
		// Set the random seed to the id of the creature to generate the same items for the same creature every time.
		std::srand(id);
		cube::Item item = cube::Item(23, std::rand() % 7);
		item.region = IntVector2(std::rand(), std::rand());
		item.modifier = std::rand();
		item.rarity = 10;
		item.formula_category = std::rand();

		if (!cube::Helper::CWGetItemsSold(game->world, item, id))
		{
			itemVector->at(0).push_back(cube::ItemStack(1, item));

			// Test
			wchar_t buffer[250];
			swprintf_s(buffer, 250, L"Player ptr: %012X\n", game->GetPlayer());
			game->PrintMessage(buffer, 0, 255, 0);
			swprintf_s(buffer, 250, L"Item ptr: %012X\n", &itemVector->at(0).at(0).item);
			game->PrintMessage(buffer, 0, 255, 0);
		}
	}
}
static void UpdateItemVendorShop(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, long long id)
{
	std::srand(id);
	const static int SPECIALS[] = {
		1, 2, 3, 18, 12, 14, 15, 16, 17,
	};

	int max = sizeof(SPECIALS) / sizeof(*SPECIALS);
	for (int i = 0; i < max; i++)
	{
		cube::Item item = cube::Item(24, SPECIALS[i]);
		item.rarity = 0;
		item.region = game->GetPlayer()->entity_data.current_region;

		if (!cube::Helper::CWGetItemsSold(game->world, item, id))
		{
			itemVector->at(0).push_back(cube::ItemStack(1, item));
		}
	}
}
static void UpdateWeaponVendorShop(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, long long id)
{
	// Add 4 spirit cubes
	for (int i = 0; i < 4; i++)
	{
		cube::Item item = cube::SpiritCube::Create((cube::SpiritCube::Type)((int)cube::SpiritCube::Type::FireSpirit + i));

		int count = 5;
		int sold = cube::Helper::CWGetItemsSold(game->world, item, id);

		if (sold < count)
		{
			itemVector->at(0).push_back(cube::ItemStack(count - sold, item));
		}
	}
}