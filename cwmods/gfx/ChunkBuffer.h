#ifndef GFX_CHUNKBUFFER_H
#define GFX_CHUNKBUFFER_H
#include "../IDA/types.h"

namespace gfx {
class D3D11VertexBuffer;
class D3D11IndexBuffer;
class ChunkBuffer {
    public:
		virtual ~ChunkBuffer();

		gfx::D3D11VertexBuffer* vertex_buffer;
		gfx::D3D11IndexBuffer* index_buffer;
		__int64 field_18;
		__int64 field_20;
		__int64 field_28;
		__int64 field_30;
		__int64 field_38;
		__int64 field_40;
		__int64 field_48;
		__int64 field_50;
		__int64 field_58;
    };
}


static_assert(sizeof(gfx::ChunkBuffer) == 0x60, "gfx::ChunkBuffer is not the correct size.");

#endif // GFX_CHUNKBUFFER_H
