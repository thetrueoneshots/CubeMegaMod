#ifndef D3D11RENDERER_H
#define D3D11RENDERER_H

#include "../IDA/types.h"
#include "Renderer.h"

namespace gfx {
class D3D11Renderer : public Renderer {
    public:
		virtual ~D3D11Renderer();

		_BYTE gap540[1287];
		char end;

		void RemeshZone(int x, int y);
    };
}

static_assert(sizeof(gfx::D3D11Renderer) == 0xA48, "gfx::D3D11Renderer is not the correct size.");

#endif // D3D11RENDERER_H
