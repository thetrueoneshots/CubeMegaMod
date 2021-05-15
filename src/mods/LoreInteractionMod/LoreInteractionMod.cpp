#include "LoreInteractionMod.h"

static void AnnounceFoundLoreItem(cube::Game* game, int type)
{
	const static wchar_t* places[] = {
		L"hidden behind the description",
		L"burried in the ground",
		L"covered in mud",
		L"next to the object",
		L"by accident",
	};
	const static int places_size = sizeof(places) / sizeof(*places);

	const static wchar_t* verbs[] = {
		L"found",
		L"stumbled upon",
		L"came accross",
		L"detected",
		L"uncovered",
		L"noticed",
	};
	const static int verbs_size = sizeof(verbs) / sizeof(*verbs);

	const static wchar_t* item_types[] = {
		L"some gear",
		L"a weapon",
		L"an artifact",
	};
	const static wchar_t* endings[] = {
		L"!",
		L"."
	};

	wchar_t buffer[250];
	
	swprintf_s(buffer, 250,
		L"You %s %s %s%s\n",
		verbs[cube::Helper::RandomInt() % verbs_size],
		item_types[type],
		places[cube::Helper::RandomInt() % places_size],
		endings[cube::Helper::RandomInt() % 2]
	);

	game->PrintMessage(buffer, 255, 165, 0);
	//game->PrintMessage(L"You found some gear!\n", 255, 165, 0);
}

void LoreInteractionMod::OnLoreIncrease(cube::Game* game, int value)
{
	cube::Creature* player = game->GetPlayer();
	int chance = cube::Helper::RandomInt() % 100;
	int compare = 0;
	if (value < 100)
	{

		// value % (max 50%) chance for 1 star gear
		compare = min(value, 50);
		if (chance <= compare)
		{
			cube::Item item = cube::Helper::GenerateItem(cube::Helper::ItemGenerationType::Gear, player->entity_data.current_region);
			item.rarity = 0;
			cube::Helper::DropItem(player, item);

			AnnounceFoundLoreItem(game, 0);
		}

		// [Possible] Drop gold
	}
	else if (value < 150)
	{
		compare = (value - 100);
		// (value - 100)% chance of a 2-3 star weapon drop
		if (chance <= compare)
		{
			cube::Item item = cube::Helper::GenerateItem(cube::Helper::ItemGenerationType::Gear, player->entity_data.current_region);
			item.rarity = 1 + cube::Helper::RandomInt() % 2;
			item.category = 3;
			item.id = cube::Helper::RandomInt() % 18;
			cube::Helper::DropItem(player, item);

			AnnounceFoundLoreItem(game, 1);
		}
	}
	else
	{
		compare = min((value - 150)/5, 40);
		// (value - 150)/5 % chance of an artifact drop until a max of 40%
		if (chance <= compare)
		{
			cube::Helper::DropItem(player, cube::Helper::ItemGenerationType::Artifact);

			AnnounceFoundLoreItem(game, 2);
		}
	}
}
