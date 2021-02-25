#ifndef CUBE_INVENTORYWIDGET_H
#define CUBE_INVENTORYWIDGET_H
#include "BaseWidget.h"
#include "../plasma/Node.h"
#include <list>
namespace cube {
class Game;
class InventoryWidget : public cube::BaseWidget {
    public:
		int64_t field_1E8;
		int64_t field_1F0;
		int64_t field_1F8;
		int64_t field_200;
		int64_t field_208;
		cube::Game* game;
		plasma::Node* field_218;
		int64_t field_220;
		plasma::Node* field_228;
		plasma::Node* up_button;
		plasma::Node* up_button_related;
		plasma::Node* down_button_related;
		plasma::Node* scroll_button_related;
		plasma::Node* left_button_related;
		plasma::Node* wideitembox;
		std::list<void*> unk_list_0x260_node_size_0x18;
		int64_t field_270;
		int64_t field_278;
		int32_t unk_inv_index_thing;
		int32_t field_284;
		int64_t field_288;
		int64_t field_290;
		int64_t field_298;
		bool field_2A0;
		bool field_2A1;
		bool field_2A2;
		bool field_2A3;
		int32_t field_2A4;
		int32_t field_2A8;
		int32_t field_2AC;
		int32_t field_2B0;
		int32_t field_2B4;
		int64_t field_2B8;
		int64_t field_2C0;
		int64_t field_2C8;
    };
}

static_assert(sizeof(cube::InventoryWidget) == 0x2D0, "cube::InventoryWidget is not the correct size.");

#endif // CUBE_INVENTORYWIDGET_H
