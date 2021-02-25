#include "Chunk.h"

#include <windows.h>

void gfx::Chunk::Remesh() {
	remesh_time = timeGetTime();
	needs_remesh = true;
}