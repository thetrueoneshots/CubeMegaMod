#ifndef WIDGET_H
#define WIDGET_H

#include "../IDA/types.h"
#include "NamedObject.h"
#include "../common/Matrix4.h"

namespace plasma {
	class Node;
    class Widget : public plasma::NamedObject {
        public:
			virtual void Draw(); //I don't know what controls the position where the widget gets drawn

			void* deformer_vtable;
			float scale;
			_BYTE gap44[20];
			__int64 d3d11_render_surface_ptr;
			Matrix4 matrix;
			__int64 field_A0;
			_BYTE gapA8[208];
			plasma::Node* node;
			_BYTE gap180[39];
			char end;
        };
}

static_assert(sizeof(plasma::Widget) == 0x1A8, "plasma::Widget is not the correct size.");

#endif // WIDGET_H
