#ifndef CUBE_ADAPTIONWIDGET_H
#define CUBE_ADAPTIONWIDGET_H

#include "BaseWidget.h"
#include "../plasma/Node.h"

namespace cube {
class Game;
class Item;
class AdaptionWidget : public cube::BaseWidget {
    public:
		cube::Item* item;
		cube::Game* game;
		plasma::Node* itemframe;
		plasma::Node* rightarrow;
    };
}

static_assert(sizeof(cube::AdaptionWidget) == 0x208, "cube::AdaptionWidget is not the correct size.");

#endif // CUBE_ADAPTIONWIDGET_H
