#ifndef KEYABLE_H
#define KEYABLE_H

#include "../IDA/types.h"
#include "NamedObject.h"

namespace plasma {
    class Keyable : public plasma::NamedObject {
        public:
            __int64 field_38;
            __int64 field_40;
            __int64 field_48;
            __int64 field_50;
            __int64 field_58;
            __int64 field_60;
            __int64 field_68;
        };
}

#endif // KEYABLE_H
