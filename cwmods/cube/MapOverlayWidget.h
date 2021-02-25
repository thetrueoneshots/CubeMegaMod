#ifndef CUBE_MAPOVERLAYWIDGET_H
#define CUBE_MAPOVERLAYWIDGET_H
#include "../plasma/Widget.h"
#include "../common/Vector2.h"
#include "Item.h"

namespace cube {
class Game;
class MapOverlayWidget : public plasma::Widget {
    public:
		cube::Game* game;
		cube::Item hovered_artifact;
		IntVector2 some_vec_for_preview_widget_but_not_artifacts;
		char field_258;
		char field_259;
		char field_25A;
		char field_25B;
		int field_25C;
    };
}

static_assert(sizeof(cube::MapOverlayWidget) == 0x260, "cube::MapOverlayWidget is not the correct size.");

#endif // CUBE_MAPOVERLAYWIDGET_H
