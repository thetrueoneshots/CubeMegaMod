#ifndef NAMEDOBJECT_H
#define NAMEDOBJECT_H

#include "../IDA/types.h"
#include "Object.h"

namespace plasma {
    class NamedObject : public plasma::Object {
        public:
            void *field_18;
            __int64 field_20;
            __int64 field_28;
            __int64 field_30;
        };
}

#endif // NAMEDOBJECT_H
