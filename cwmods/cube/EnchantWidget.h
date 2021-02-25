#ifndef CUBE_ENCHANTWIDGET_H
#define CUBE_ENCHANTWIDGET_H

#include "BaseWidget.h"
#include "../plasma/Node.h"


namespace cube {
class Game;
class EnchantWidget : public cube::BaseWidget {
    public:
		int inventory_tab_index;
		int inventory_item_index;
		int can_identify;
		int field_1F4;
		cube::Game* game;
		plasma::Node* itemframe;
    };
}

static_assert(sizeof(cube::EnchantWidget) == 0x208, "cube::EnchantWidget is not the correct size.");

#endif // CUBE_ENCHANTWIDGET_H
