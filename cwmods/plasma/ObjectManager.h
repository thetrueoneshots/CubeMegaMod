#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include "../IDA/types.h"

namespace plasma {
    class ObjectManager {
        public:
            void *vtable;
            __int64 field_8;
            __int64 field_10;
            __int64 field_18;
        };
}

#endif // OBJECTMANAGER_H
