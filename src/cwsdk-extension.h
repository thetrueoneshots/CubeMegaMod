/*
* This is a header file for including all the cwsdk-extension code.
*/

#include "cwsdk-extension/events/AddGoldEvent.h"
#include "cwsdk-extension/events/DivingEvent.h"
#include "cwsdk-extension/events/Event.h"
#include "cwsdk-extension/events/EventList.h"

#include "cwsdk-extension/creature/Creature.h"
#include "cwsdk-extension/creature/CreatureFactory.h"

#include "cwsdk-extension/ability/Ability.h"
#include "cwsdk-extension/ability/HealAbility.h"
#include "cwsdk-extension/ability/FarJumpAbility.h"
#include "cwsdk-extension/ability/ConvertMTSAbility.h"

#include "cwsdk-extension/button/DButton.h"

#include "cwsdk-extension/helper/Helper.h"

#include "cwsdk-extension/Inventory.h"
#include "cwsdk-extension/Timer.h"

#include "cwsdk.h"

namespace cube
{
	namespace Helper
	{
		bool InGUI(cube::Game* game)
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
	}
}
