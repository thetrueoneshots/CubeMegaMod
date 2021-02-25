#include "SpriteManager.h"
#include "../cwsdk.h"

void cube::SpriteManager::LoadSprites()
{
	((void(*)(cube::SpriteManager*, std::string))CWOffset(0x177F50))(this, std::string("sprites"));
}

cube::Sprite* cube::SpriteManager::CreateSprite()
{
	return cube::Sprite::Create(this->gfx_D3D11Graphics);
}

void cube::SpriteManager::ParseCubToSprite(Sprite* sprite, std::string file) {
	((void(*)(Sprite*, std::string, uint8_t, uint8_t, uint8_t))CWOffset(0x16F320))(sprite, file, 0, 1, 0);
}
