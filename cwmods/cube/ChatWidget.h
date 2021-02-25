#ifndef CHATWIDGET_H
#define CHATWIDGET_H
#include "../common/RGBA.h"
#include "../plasma/Widget.h"
#include "../plasma/ScalableFont.h"
#include <string>
#include <list>
namespace cube {
class ChatWidget : public plasma::Widget {
    public:
		class MessageData {
		public:
			std::wstring text;
			ByteRGBA color;
			char field_24;
			char field_25;
			char field_26;
			char field_27;
		};


		std::list<std::list<MessageData>> message_sections;
		std::wstring typebox_text;
		bool typebox_active;
		plasma::ScalableFont* scalable_font;
		int typebox_cursor_position;
		int backwards_highlight_length;

		void PrintMessage(std::wstring* message, FloatRGBA* color);
        void PrintMessage(const wchar_t* message, FloatRGBA* color);
        void PrintMessage(const wchar_t* message);
        void PrintMessage(const wchar_t* message, char red, char green, char blue);
    };
}
static_assert(sizeof(cube::ChatWidget) == 0x1F0, "cube::ChatWidget is not the correct size.");
#endif // CHATWIDGET_H
