#ifndef CUBE_CONTROLSWIDGET_H
#define CUBE_CONTROLSWIDGET_H

#include "BaseWidget.h"
#include "Controls.h"
#include "../plasma/Node.h"

namespace cube {
class Game;
class ControlsWidget : public cube::BaseWidget {
    public:
		cube::Game* game;
		cube::Controls controls;
		plasma::Node* ok_button;
		plasma::Node* cancel_button;
		plasma::Node* defaults_button;
		plasma::Node* upbutton;
		plasma::Node* downbutton;
		plasma::Node* scrollbutton;
		int scroll_position;
		int hovered_index;
		int selected_index;
		int field_2E4;
    };
}

static_assert(sizeof(cube::ControlsWidget) == 0x2E8, "cube::ControlsWidget is not the correct size.");

#endif // CUBE_CONTROLSWIDGET_H
