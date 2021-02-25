#ifndef NODE_H
#define NODE_H

#include "../IDA/types.h"
#include "../common/types.h"
#include "NamedObject.h"
#include "Vector.h"

namespace plasma {
	class Transformation;
	class Display;
	class Widget;
    class Node : public plasma::NamedObject {
        public:
			__int64 field_38;
			plasma::Node* parent;
			__int64 field_48;
			__int64 field_50;
			__int64 field_58;
			plasma::Transformation* transformation;
			plasma::Display* display;
			plasma::Widget* widget1;
			plasma::Widget* widget2;
			__int64 field_80;
			__int64 field_88;
			__int64 field_90;
			__int64 field_98;
			__int64 field_A0;
			__int64 field_A8;
			__int64 field_B0;
			__int64 field_B8;
			__int64 field_C0;

			void Translate(plasma::Vector<2, float>* base, plasma::Vector<2, float>* offset);
			void Translate(float baseX, float baseY, float offsetX, float offsetY);
			i32 Draw(u32 flags);
        };
}

#endif // NODE_H
