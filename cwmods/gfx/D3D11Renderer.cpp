#include "D3D11Renderer.h"
#include "../cwsdk.h"

void gfx::D3D11Renderer::RemeshZone(int x, int y) {
	((void(*)(gfx::D3D11Renderer*, int, int))CWOffset(0xE9530))(this, x, y);
}