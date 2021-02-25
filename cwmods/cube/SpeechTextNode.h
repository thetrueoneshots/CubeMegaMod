#ifndef CUBE_SPEECHTEXTNODE_H
#define CUBE_SPEECHTEXTNODE_H

#include <list>
#include <string>

namespace cube {
class SpeechTextNode {
    public:
		virtual ~SpeechTextNode();

		std::list<void*> field_8;
		std::list<void*> field_18;
		std::list<void*> field_28;
		std::list<void*> field_38;
		char some_char_or_bool;
		char pad_49;
		char pad_4A;
		char pad_4B;
		char pad_4C;
		char pad_4D;
		char pad_4E;
		char pad_4F;
		__int64 some_ptr_probably_list;
		int field_58;
		int field_5C;
		std::wstring some_string;
		cube::SpeechTextNode* speechtextnode;
		std::list<void*> unk_list_0x18_node;
		int field_98;
		int pad_9C;
    };
}

static_assert(sizeof(cube::SpeechTextNode) == 0xA0, "cube::SpeechTextNode is not the correct size.");

#endif // CUBE_SPEECHTEXTNODE_H
