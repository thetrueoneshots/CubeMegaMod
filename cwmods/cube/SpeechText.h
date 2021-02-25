#ifndef CUBE_SPEECHTEXT_H
#define CUBE_SPEECHTEXT_H

#include "SpeechTextNode.h"
#include <list>

namespace cube {
class SpeechText {
    public:
		virtual ~SpeechText();

		cube::SpeechTextNode* speechtextnode;
		__int64 field_10;
		__int64 field_18;
		__int64 field_20;
		std::list<void*> unk_list_0x30_node;
		std::list<void*> unk_list_0x40_node;
    };
}

static_assert(sizeof(cube::SpeechText) == 0x48, "cube::SpeechText is not the correct size.");

#endif // CUBE_SPEECHTEXT_H
