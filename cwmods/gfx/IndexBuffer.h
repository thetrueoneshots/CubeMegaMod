#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "../IDA/types.h"

namespace gfx {
class IndexBuffer {
    public:
		virtual ~IndexBuffer();
		virtual bool IASetIndexBuffer();
    };
}

static_assert(sizeof(gfx::IndexBuffer) == 0x8, "gfx::IndexBuffer is not the correct size.");

#endif // INDEXBUFFER_H
