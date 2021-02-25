#ifndef CUBE_MULTIPLAYER_WIDGET_H
#define CUBE_MULTIPLAYER_WIDGET_H
#include "BaseWidget.h"
#include "../plasma/Node.h"
#include "Controls.h"
#include <vector>
namespace cube {
class Game;
class MultiplayerWidget : public cube::BaseWidget {
    public:
		cube::Game* game;
		bool verify_appid;
		std::vector<std::pair<int64_t, std::wstring>> friends;
		cube::Controls controls;
		plasma::Node* leave_button;
		plasma::Node* up_button;
		plasma::Node* down_button;
		plasma::Node* scroll_bar;
		int scroll_position;
		int selected_player_index;
		bool some_bool;
		char field_2F1;
		char field_2F2;
		char field_2F3;
		char field_2F4;
		char field_2F5;
		char field_2F6;
		char field_2F7;
    };
}

static_assert(sizeof(cube::MultiplayerWidget) == 0x2F8, "cube::MultiplayerWidget is not the correct size.");

#endif // CUBE_MULTIPLAYER_WIDGET_H
