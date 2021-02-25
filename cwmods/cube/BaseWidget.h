#ifndef CUBE_BASEWIDGET_H
#define CUBE_BASEWIDGET_H

#include "../plasma/Widget.h"
#include "../plasma/ScalableFont.h"
namespace cube {
class BaseWidget : public plasma::Widget {
    public:
		plasma::ScalableFont* scalable_font;
		float field_1B0;
		float field_1B4;
		float field_1B8;
		float field_1BC;
		float field_1C0;
		float field_1C4;
		float field_1C8;
		float field_1CC;
		float field_1D0;
		float field_1D4;
		float field_1D8;
		float field_1DC;
		float field_1E0;
		float field_1E4;
    };
}


static_assert(sizeof(cube::BaseWidget) == 0x1E8, "cube::BaseWidget is not the correct size.");
#endif // CUBE_BASEWIDGET_H
