#ifndef D3D11INDEXBUFFER_H
#define D3D11INDEXBUFFER_H

#include "../IDA/types.h"
#include "IndexBuffer.h"
#include <d3d11.h>

namespace gfx {
class D3D11IndexBuffer : public IndexBuffer {
    public:
		ID3D11DeviceContext* pImmediateContext;
		ID3D11Buffer* buffer;
		unsigned int format;
		int field_1C;
    };
}

static_assert(sizeof(gfx::D3D11IndexBuffer) == 0x20, "gfx::D3D11IndexBuffer is not the correct size.");

#endif // D3D11INDEXBUFFER_H
