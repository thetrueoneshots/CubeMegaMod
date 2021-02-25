#ifndef GFX_CHUNK_H
#define GFX_CHUNK_H
#include "../IDA/types.h"
#include <list>

namespace gfx {
class ChunkBuffer;
class Chunk {
    public:
		virtual ~Chunk();

		//Data members
		std::list<gfx::ChunkBuffer*> chunkbuffers;
		std::list<gfx::ChunkBuffer*> new_chunkbuffers;
		_BYTE gap28[80];
		int remesh_time;
		bool needs_remesh;
		_BYTE gap7D[519];
		char field_284;
		_BYTE gap285[2];
		char end;

		void Remesh();
    };
}


static_assert(sizeof(gfx::Chunk) == 0x288, "gfx::Chunk is not the correct size.");

#endif // GFX_CHUNK_H
