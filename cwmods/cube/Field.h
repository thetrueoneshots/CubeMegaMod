#ifndef FIELD_H
#define FIELD_H

#include "../IDA/types.h"
#include "Block.h"
#include <vector>

namespace cube {
class Field {
    public:
		virtual ~Field();

		float field_8;
		float field_C;
		float field_10;
		float field_14;
		float field_18;
		float field_1C;
		float field_20;
		float field_24;
		float field_28;
		float field_2C;
		int field_30;
		int field_34;
		float field_38;
		int base_z;
		std::vector<cube::Block> blocks;
    };
}

static_assert(sizeof(cube::Field) == 0x58, "cube::Field is not the correct size.");

#endif // FIELD_H
