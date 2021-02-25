#ifndef CUBE_PREVIEWWIDGET_H
#define CUBE_PREVIEWWIDGET_H

#include "BaseWidget.h"

namespace cube {
class Game;
class Item;
class PreviewWidget : public cube::BaseWidget {
    public:
		__int64 field_1E8;
		cube::Item* target_item;
		__int64 field_1F8;
		signed int field_200;
		int field_204;
		__int64 field_208;
		cube::Item* current_item;
		__int64 field_218;
		__int64 field_220;
		__int64 field_228;
    };
}

static_assert(sizeof(cube::PreviewWidget) == 0x230, "cube::PreviewWidget is not the correct size.");

#endif // CUBE_PREVIEWWIDGET_H
