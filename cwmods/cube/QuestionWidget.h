#ifndef CUBE_QUESTIONWIDGET_H
#define CUBE_QUESTIONWIDGET_H

#include "BaseWidget.h"
#include "../plasma/Node.h"
#include "Item.h"

namespace cube {
class Game;
class QuestionWidget : public cube::BaseWidget {
    public:
		__int64 field_1E8;
		__int64 field_1F0;
		__int64 field_1F8;
		__int64 field_200;
		cube::Game* game;
		__int64 field_210;
		__int64 field_218;
		__int64 field_220;
		__int64 field_228;
		__int64 field_230;
		float field_238;
		int field_23C;
		char field_240;
		char field_241;
		char field_242;
		char field_243;
		char field_244;
		char field_245;
		char field_246;
		char field_247;
		char field_248;
		char field_249;
		char field_24A;
		char field_24B;
		char field_24C;
		char field_24D;
		char field_24E;
		char field_24F;
		cube::Item item;
		__int64 field_2F0;
		__int64 field_2F8;
    };
}

static_assert(sizeof(cube::QuestionWidget) == 0x300, "cube::QuestionWidget is not the correct size.");

#endif // CUBE_QUESTIONWIDGET_H
