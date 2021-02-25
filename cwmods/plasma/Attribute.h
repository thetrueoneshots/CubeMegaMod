#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../IDA/types.h"
#include <string>

namespace plasma {
    class Attribute {
        public:
			void* vtable;
			__int64 some_0x48_ptr;
			__int64 field_10;
			__int64 some_embedded_struct;
			__int64 field_20;
			__int64 field_28;
			__int64 field_30;
			int field_38;
			int current_frame;
			std::string name;
			__int64 field_60;
			__int64 field_68;
        };
}

#endif // ATTRIBUTE_H
