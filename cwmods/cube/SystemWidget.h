#ifndef CUBE_SYSTEMWIDGET_H
#define CUBE_SYSTEMWIDGET_H

#include "BaseWidget.h"
#include "../plasma/Node.h"


namespace cube {
class Game;
class SystemWidget : public cube::BaseWidget {
    public:
		cube::Game* game;
		int hovered_button_index;
		int field_1F4;
    };
}

static_assert(sizeof(cube::SystemWidget) == 0x1F8, "cube::SystemWidget is not the correct size.");

#endif // CUBE_SYSTEMWIDGET_H
