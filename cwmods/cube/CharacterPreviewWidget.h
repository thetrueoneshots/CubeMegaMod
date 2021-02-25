#ifndef CUBE_CHARACTERPREVIEWWIDGET_H
#define CUBE_CHARACTERPREVIEWWIDGET_H

#include "BaseWidget.h"

namespace cube {
class Game;
class Creature;
class CharacterPreviewWidget : public cube::BaseWidget {
    public:
		cube::Creature* creature;
		cube::Game* game;
    };
}

static_assert(sizeof(cube::CharacterPreviewWidget) == 0x1F8, "cube::CharacterPreviewWidget is not the correct size.");

#endif // CUBE_CHARACTERPREVIEWWIDGET_H
