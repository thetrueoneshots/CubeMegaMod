#ifndef CUBE_SPEECHWIDGET_H
#define CUBE_SPEECHWIDGET_H

#include "BaseWidget.h"
#include "Item.h"
#include <vector>
#include <list>
#include "../common/RGBA.h"
#include "../plasma/Node.h"


namespace cube {
class Game;
class SpeechWidget : public cube::BaseWidget {
    public:
		class Dialog // Start of cube::SpeechWidget::Dialog
		{
			public:
			class Phrase // Start of cube::SpeechWidget::Dialog::Phrase
			{
				public:
				std::wstring text;
				FloatRGBA color;
			}; // End of cube::SpeechWidget::Dialog::Phrase

			std::list<cube::SpeechWidget::Dialog::Phrase> phrases;
			__int64 field_10;
			__int64 field_18;
			__int64 field_20;
			__int64 field_28;
			__int64 field_30;
			__int64 field_38;
			__int64 field_40;
			__int64 field_48;
			__int64 field_50;
			__int64 field_58;
			__int64 field_60;
			__int64 field_68;
			__int64 field_70;
			__int64 field_78;
			__int64 field_80;
			__int64 field_88;
			__int64 field_90;
			__int64 field_98;
			__int64 field_A0;
			__int64 field_A8;
			__int64 field_B0;
			__int64 field_B8;
			__int64 field_C0;
			__int64 field_C8;
			int field_D0;
			int field_D4;
			cube::Item item;
			__int64 field_178;
			__int64 field_180;
			__int64 field_188;
			__int64 field_190;
			__int64 field_198;
			__int64 field_1A0;
			__int64 field_1A8;
		}; // End of cube::SpeechWidget::Dialog


		std::vector<cube::SpeechWidget::Dialog> dialogs;
		float read_time;
		int dialog_index;
		float text_uncovered;
		int field_20C;
		__int64 field_210;
		__int64 field_218;
		cube::Item item;
		__int64 field_2C0;
		__int64 field_2C8;
		__int64 field_2D0;
		cube::Game* game;
		plasma::Node* speech_next;
		plasma::Node* speech_end;
		__int64 field_2F0;
		__int64 field_2F8;
    };
}

static_assert(sizeof(cube::SpeechWidget) == 0x300, "cube::SpeechWidget is not the correct size.");
static_assert(sizeof(cube::SpeechWidget::Dialog) == 0x1B0, "cube::SpeechWidget::Dialog is not the correct size.");

#endif // CUBE_SPEECHWIDGET_H
