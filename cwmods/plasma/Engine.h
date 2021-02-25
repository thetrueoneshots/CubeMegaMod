#ifndef ENGINE_H
#define ENGINE_H

#include "../IDA/types.h"
#include "ObjectManager.h"
#include "FontEngine.h"
#include <list>
#include "Node.h"
#include "../common/Vector2.h"

namespace plasma {
    class Engine : public plasma::ObjectManager {
        public:
			_BYTE gap20[40];
			plasma::FontEngine* font_engine;
			_BYTE gap50[64];
			CRITICAL_SECTION critical_section;
			_BYTE gapB8[24];
			std::list<void*> unk_list_maybe_widgets;
			_BYTE gapE0[96];
			plasma::Node* root_node;
			_BYTE gap148[40];
			void* unk_ptr;
			__int64 field_178;
			FloatVector2 mouse_position;
			FloatVector2 previous_mouse_position;
			_BYTE gap190[255];
			char end;
        };
}
static_assert(sizeof(plasma::Engine) == 0x290, "plasma::Engine is not the correct size.");
#endif // ENGINE_H
