#ifndef CUBE_BASEWIDGET_H
#define CUBE_BASEWIDGET_H

#include "../plasma/Widget.h"
#include "../plasma/ScalableFont.h"
#include "../common/Vector2.h"
#include "../common/RGBA.h"

namespace cube {
class BaseWidget : public plasma::Widget {
    public:
		plasma::ScalableFont* scalable_font;
		float field_1B0;
		float field_1B4;
		float field_1B8;
		float field_1BC;
		float field_1C0;
		FloatRGBA draw_color;
		float field_1D4;
		float field_1D8;
		float field_1DC;
		float field_1E0;
		float field_1E4;

		float* DrawBaseWidgetText(FloatVector2 *vec, std::wstring *text, float x, float y);
		void SetDrawColor(FloatRGBA* color);
		void SetDrawColor(char r, char g, char b, char a = 255);
    };
}


static_assert(sizeof(cube::BaseWidget) == 0x1E8, "cube::BaseWidget is not the correct size.");
#endif // CUBE_BASEWIDGET_H
