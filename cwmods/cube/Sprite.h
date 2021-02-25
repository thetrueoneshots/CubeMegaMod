#ifndef CUBE_SPRITE_H
#define CUBE_SPRITE_H

#include "../IDA/types.h"
#include "../gfx/D3D11Graphics.h"
#include "../gfx/D3D11VertexBuffer.h"
#include "../gfx/D3D11IndexBuffer.h"
#include <windows.h>
#include <map>

namespace cube {
    class Sprite {
        public:
			class UnkSubstruct {
			public:
				__int64 field_0;
				__int64 field_8;
				__int64 field_10;
			};

			virtual ~Sprite();

			cube::Sprite::UnkSubstruct struct_array[3];
			std::map<void*, void*> unk_map_size_0x38;
			gfx::D3D11Graphics* gfx_D3D11graphics;
			__int64 field_68;
			gfx::D3D11VertexBuffer* gfx_D3D11VertexBuffer;
			gfx::D3D11IndexBuffer* gfx_D3D11IndexBuffer;
			unsigned int field_80;
			unsigned int field_84;
			int something_with_offset_1;
			int something_with_offset_2;
			int lowering_this_makes_plants_go_fast;
			int field_94;
			__int64 field_98;
			__int64 field_A0;

			// Methods
			static cube::Sprite* Create(gfx::D3D11Graphics* graphics);
			cube::Sprite* ctor(gfx::D3D11Graphics* graphics);
	};
       
}

static_assert(sizeof(cube::Sprite) == 0xA8, "cube::Sprite is not the correct size.");

#endif // CUBE_SPRITE_H
