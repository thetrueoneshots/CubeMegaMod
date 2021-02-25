#ifndef OBJECT_H
#define OBJECT_H

#include "../IDA/types.h"

namespace plasma {
	class D3D11Engine;
    class Object {
        public:
			virtual ~Object();

            plasma::D3D11Engine *d3d11_engine;
            __int64 field_10;
        };
}
static_assert(sizeof(plasma::Object) == 0x18, "plasma::Object is not the correct size.");
#endif // OBJECT_H
