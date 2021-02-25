#ifndef GFX_GRAPHICS_H
#define GFX_GRAPHICS_H

#include "../IDA/types.h"

namespace gfx {
class Graphics {
    public:
		virtual ~Graphics();
    };
}

static_assert(sizeof(gfx::Graphics) == 0x8, "gfx::Graphics is not the correct size.");

#endif // GFX_GRAPHICS_H
