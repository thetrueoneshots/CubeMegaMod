#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "../IDA/types.h"

namespace gfx {
class VertexBuffer {
    public:
		virtual ~VertexBuffer();
		virtual bool IASetVertexBuffers();
    };
}

#endif // VERTEXBUFFER_H
