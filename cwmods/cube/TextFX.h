#ifndef CUBE_TEXTFX_H
#define CUBE_TEXTFX_H

#include "../common/Vector3.h"
#include "../common/Vector2.h"
#include "../common/RGBA.h"

#include <string>

namespace cube {
class TextFX {
    public:
		int animation_time;
		float distance_to_fall;
		LongVector3 position;
		FloatVector2 offset_2d;
		FloatRGBA color;
		std::wstring text;
		int animation_length;
		float size;
		int field_60;
		//plus 4 bytes padding

		TextFX();
    };
}

static_assert(sizeof(cube::TextFX) == 0x68, "cube::TextFX is not the correct size.");

#endif // CUBE_TEXTFX_H
