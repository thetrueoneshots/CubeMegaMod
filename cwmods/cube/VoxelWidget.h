#ifndef CUBE_VOXELWIDGET_H
#define CUBE_VOXELWIDGET_H

#include "BaseWidget.h"
#include "../plasma/Node.h"
#include "ItemStack.h"
#include "../common/Vector3.h"
#include <vector>

namespace cube {
class Game;
class VoxelWidget : public cube::BaseWidget {
    public:
		FloatVector3 rotation;
		int field_1F4;
		std::vector<cube::ItemStack> available_customizations;
		int selected_upgrade_index;
		cube::Item selected_upgrade_item;
		int field_2B4;
		cube::Game* game;
		int selected_item_index;
		int hovered_item_index;
		IntVector3 voxel_placement_position;
		int field_2D4;
		int hovered_upgrade_index;
		cube::Item preview_upgrade_item;
		bool holding_placed_upgrade;
		char field_37D;
		char field_37E;
		char field_37F;
		IntVector3 upgrade_pickup_location;
		BYTE upgrade_pickup_material;
		char field_38D;
		char field_38E;
		char field_38F;
    };
}

static_assert(sizeof(cube::VoxelWidget) == 0x390, "cube::VoxelWidget is not the correct size.");

#endif // CUBE_VOXELWIDGET_H
