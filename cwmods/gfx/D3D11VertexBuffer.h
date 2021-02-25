#ifndef D3D11VERTEXBUFFER_H
#define D3D11VERTEXBUFFER_H

#include "../IDA/types.h"
#include "VertexBuffer.h"
#include <d3d11.h>

namespace gfx {
class D3D11VertexBuffer : public VertexBuffer {
    public:
		virtual ~D3D11VertexBuffer();

		ID3D11DeviceContext* pImmediateContext;
		ID3D11Buffer* buffer;
    };
}

static_assert(sizeof(gfx::D3D11VertexBuffer) == 0x18, "gfx::D3D11VertexBuffer is not the correct size.");

#endif // D3D11VERTEXBUFFER_H
