#ifndef CUBE_CHARACTESTYLERWIDGET_H
#define CUBE_CHARACTESTYLERWIDGET_H

#include "BaseWidget.h"
#include "../plasma/Node.h"
#include "../common/ColorRGB.h"

namespace cube {
class Game;
class CharacterStyleWidget : public cube::BaseWidget {
    public:
		cube::Game* game;
		plasma::Node* race_left_button;
		plasma::Node* race_right_button;
		plasma::Node* class_left_button;
		plasma::Node* class_right_button;
		plasma::Node* gender_left_button;
		plasma::Node* gender_right_button;
		plasma::Node* face_left_button;
		plasma::Node* face_right_button;
		plasma::Node* haircut_left_button;
		plasma::Node* haircut_right_button;
		int race;
		int class_type;
		int gender;
		int face;
		int haircut;
		ByteRGB current_hair_color;
		ByteRGB preview_hair_color;
		// 6 bytes padding
    };
}

static_assert(sizeof(cube::CharacterStyleWidget) == 0x260, "cube::CharacterStyleWidget is not the correct size.");

#endif // CUBE_CHARACTESTYLERWIDGET_H
