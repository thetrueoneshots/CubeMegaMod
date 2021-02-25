#include "Sprite.h"
#include "../cwsdk.h"

cube::Sprite::~Sprite()
{
}

cube::Sprite* cube::Sprite::Create(gfx::D3D11Graphics* graphics) {
	cube::Sprite* newSprite = (cube::Sprite*)new char[sizeof(cube::Sprite)];
	newSprite->ctor(graphics);
	return newSprite;
}

cube::Sprite* cube::Sprite::ctor(gfx::D3D11Graphics* graphics)
{
    return ((cube::Sprite * (*)(cube::Sprite*, gfx::D3D11Graphics*, uint8_t unk))CWOffset(0x16E6B0))(this, graphics, 0);
}
