#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include "../IDA/types.h"
#include <windows.h>
#include "../gfx/D3D11Graphics.h"
#include "Sprite.h"
#include <vector>
#include <string>

namespace cube {
    class SpriteManager {
        public:
			virtual ~SpriteManager();

			gfx::D3D11Graphics* gfx_D3D11Graphics;
			std::vector<Sprite*> sprites;
			std::map<void*, void*> unk_map_node_size_0x30;
			//std::map<uint8_t, std::vector<Sprite*>> unk_map_node_size_0x30;
			std::vector<Sprite*> environment_sprites;
			std::vector<Sprite*> building_part_sprites;
			std::vector<Sprite*> cage_sprites;

			// Methods
			void LoadSprites();
			cube::Sprite* CreateSprite();
			void ParseCubToSprite(Sprite* sprite, std::string file);
        };
}

static_assert(sizeof(cube::SpriteManager) == 0x80, "cube::SpriteManager is not the correct size.");

#endif // SPRITEMANAGER_H
