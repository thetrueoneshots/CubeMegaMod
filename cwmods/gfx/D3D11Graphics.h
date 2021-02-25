#ifndef D3D11GRAPHICS_H
#define D3D11GRAPHICS_H

#include "../IDA/types.h"
#include "Graphics.h"
#include <d3d11.h>

namespace gfx {
class D3D11Graphics : public Graphics {
    public:
		virtual ~D3D11Graphics();
		ID3D11Device* pDevice;
		ID3D11DeviceContext* pImmediateContext;
    };
}

static_assert(sizeof(gfx::D3D11Graphics) == 0x18, "gfx::D3D11Graphics is not the correct size.");

#endif // D3D11GRAPHICS_H
