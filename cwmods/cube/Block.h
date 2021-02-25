#ifndef CUBE_BLOCK_H
#define CUBE_BLOCK_H
#include "../common/types.h"
#include "../IDA/types.h"
#include "BlockProperties.h"

namespace cube {
class Block : public cube::BlockProperties<u8>{
    public:
    };
}

static_assert(sizeof(cube::Block) == 0x6, "cube::Block is not the correct size.");

#endif // CUBE_BLOCK_H
