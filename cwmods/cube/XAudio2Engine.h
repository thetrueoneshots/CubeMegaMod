#ifndef CUBE_XAUDIO2ENGINE_H
#define CUBE_XAUDIO2ENGINE_H

#include "../IDA/types.h"
#include "Music.h"

namespace cube {
class XAudio2Engine {
    public:
		virtual ~XAudio2Engine();

		void* ppXAudio2;
		__int64 field_10;
		__int64 field_18;
		__int64 field_20;
		__int64 field_28;
		__int64 field_30;
		__int64 field_38;
		__int64 field_40;
		cube::Music* music1;
		cube::Music* music2;
		__int64 field_58;
		int field_60;
		int field_64;
    };
}

static_assert(sizeof(cube::XAudio2Engine) == 0x68, "cube::XAudio2Engine is not the correct size.");

#endif // CUBE_XAUDIO2ENGINE_H
