#ifndef CUBE_HELPWIDGET_H
#define CUBE_HELPWIDGET_H

#include "BaseWidget.h"

namespace cube {
class Game;
class HelpWidget : public cube::BaseWidget {
    public:
		cube::Game* game;
    };
}

static_assert(sizeof(cube::HelpWidget) == 0x1F0, "cube::HelpWidget is not the correct size.");

#endif // CUBE_HELPWIDGET_H
