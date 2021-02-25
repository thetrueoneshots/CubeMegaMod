#ifndef CUBE_CONTROLS_H
#define CUBE_CONTROLS_H

#include <cstdint>

namespace cube {
    class Controls {
	public:
		int32_t button_attack;
		int32_t button_attack_2;
		int32_t button_special_attack;
		int32_t button_special_attack_2;
		int32_t button_class_skill;
		int32_t button_class_skill_2;
		int32_t button_ultimate_skill;
		int32_t button_ultimate_skill_2;
		int32_t button_quick_item;
		int32_t button_quick_item_2;
		int32_t button_up;
		int32_t button_up_2;
		int32_t button_down;
		int32_t button_down_2;
		int32_t button_left;
		int32_t button_left_2;
		int32_t button_right;
		int32_t button_right_2;
		int32_t button_jump;
		int32_t button_jump_2;
		int32_t button_dodge;
		int32_t button_dodge_2;
		int32_t button_use;
		int32_t button_use_2;
		int32_t button_lamp;
		int32_t button_lamp_2;
		int32_t button_walk;
		int32_t button_walk_2;
		int32_t button_call_pet;
		int32_t button_call_pet_2;
		int32_t button_world_map;
		int32_t button_world_map_2;
		int32_t button_ring_menu;
		int32_t button_ring_menu_2;
		int32_t button_inventory;
		int32_t button_inventory_2;
		int32_t button_crafting_menu;
		int32_t button_crafting_menu_2;
		int32_t button_system_menu;
		int32_t button_system_menu_2;
		int32_t button_multiplayer_menu;
		int32_t button_multiplayer_menu_2;
		int32_t button_zoom_in;
		int32_t button_zoom_in_2;
		int32_t button_zoom_out;
		int32_t button_zoom_out_2;
    };
}

static_assert(sizeof(cube::Controls) == 0xB8, "cube::Controls is not the correct size.");

#endif // CUBE_CONTROLS_H
