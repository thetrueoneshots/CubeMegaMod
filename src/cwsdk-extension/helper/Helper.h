#pragma once

#include "cwsdk.h"

namespace cube::Helper
{
	enum class ItemGenerationType
	{
		Artifact = 0,
		Pet,
		Gold,
		Gear,
		Consumable,
	};

	int CWGetItemsSold(cube::World* world, cube::Item item, long long seller_id);

	void AnnounceItem(cube::Game* game, cube::Item* item, unsigned int count, cube::Creature* creature);
	void LevelUp(cube::Creature* player);
	cube::Item GenerateItem(ItemGenerationType type, IntVector2 region = IntVector2(0, 0));
	void DropItem(cube::Creature* creature, const cube::Item& item, int amount = 1);
	void DropItem(cube::Creature* creature, ItemGenerationType type, int amount = 1);

	inline bool InGUI(cube::Game* game)
	{
		cube::GUI* gui = &game->gui;
		plasma::Node* nodes[] = {
			gui->startmenu_node,
			gui->character_selection_node,
			gui->character_creation_node,
			gui->world_selection_node,
			gui->world_creation_node,
			gui->equipment_inventory_widget->node,
			gui->crafting_inventory_widget->node,
			gui->multiplayer_widget->node,
			gui->vendor_inventory_widget->node,
			gui->adaption_widget->node,
			gui->voxel_widget->node,
			gui->enchant_widget->node,
			gui->question_widget->node,
			gui->system_widget->node,
			gui->controls_widget->node,
			gui->options_widget->node
		};

		for (plasma::Node* node : nodes) {
			if (!node) continue;
			auto data = &node->display->visibility.data;
			auto frame = node->display->visibility.current_frame;

			if (data->at(frame)) {
				return true;
			}
		}

		if (gui->chat_widget->typebox_active) return true;
		if (gui->map_open) return true;
		if (gui->esc_menu_displayed) return true;

		return false;
	}

	void LoreInteraction(cube::Creature* player, int percentage);

	bool PositionContainsWater(const LongVector3& position);

	inline static int RandomInt()
	{
		static long long count = 0;
		int random = rand();
		count += random;
		if (count >= 1000 * INT_MAX)
		{
			count -= 1000 * INT_MAX;
		}
		std::srand(random + count);
		return random;
	}
	
	inline static float RandomZeroToOne()
	{
		return (float)(RandomInt() / (float)(RAND_MAX));
	}

	inline void DisableCreatureFloating()
	{
		WriteByte(CWOffset(0x2BF67A), 0xEB);
	}

	inline void EnableCreatureFloating()
	{
		WriteByte(CWOffset(0x2BF67A), 0xFF);
	}
}