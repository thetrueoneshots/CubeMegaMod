#ifndef CUBE_CHARACTERWIDGET_H
#define CUBE_CHARACTERWIDGET_H

#include "BaseWidget.h"
#include "../plasma/Node.h"

namespace cube {
class Game;
class CharacterWidget : public cube::BaseWidget {
    public:
		cube::Game* game;
    };
}

static_assert(sizeof(cube::CharacterWidget) == 0x1F0, "cube::CharacterWidget is not the correct size.");

#endif // CUBE_CHARACTERWIDGET_H
