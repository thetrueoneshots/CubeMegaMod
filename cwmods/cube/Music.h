#ifndef CUBE_MUSIC_H
#define CUBE_MUSIC_H

#include "../IDA/types.h"
#include <windows.h>

namespace cube {
class Music {
    public:
		class UnkSubstruct1 {
			public:
				_BYTE gap0[655359];
				char end;
		};


		virtual ~Music();

		cube::Music::UnkSubstruct1 array_of_structs_3_size_0xA0000[3];
		__int64 pXAudio2Impl;
		__int64 some_struct_ptr;
		char some_bool;
		char some_bool_maybe_0;
		BYTE some_bool_maybe_1;
		char some_bool_maybe_2;
		unsigned int index_of_unk_0xA0000_substruct;
		_BYTE gap1E0020[8];
		char some_struct_size_0x348[840];
    };
}

static_assert(sizeof(cube::Music) == 0x1E0370, "cube::Music is not the correct size.");

#endif // CUBE_MUSIC_H
