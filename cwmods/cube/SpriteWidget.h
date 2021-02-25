#ifndef CUBE_SPRITEWIDGET_H
#define CUBE_SPRITEWIDGET_H

#include "BaseWidget.h"
#include "Item.h"


// If the item's category is 0, it will try to use the sprite pointer instead.
// This seems to be an unused feature in the actual game? Sprite pointer is always null.
namespace cube {
class Game;
class Sprite;
class SpriteWidget : public cube::BaseWidget {
    public:
		cube::Sprite* sprite;
		__int64 field_1F0;
		cube::Item item;
		cube::Game* game;
    };
}

static_assert(sizeof(cube::SpriteWidget) == 0x2A0, "cube::SpriteWidget is not the correct size.");

#endif // CUBE_SPRITEWIDGET_H
