#ifndef CUBE_EQUIPMENT_H
#define CUBE_EQUIPMENT_H
#include "Item.h"

namespace cube {
class Equipment {
    public:
		cube::Item unk_item;
		cube::Item neck;
		cube::Item chest;
		cube::Item feet;
		cube::Item hands;
		cube::Item shoulder;
		cube::Item weapon_left;
		cube::Item weapon_right;
		cube::Item ring_left;
		cube::Item ring_right;
		cube::Item pet;
    };
}

static_assert(sizeof(cube::Equipment) == 0x6E0, "cube::Equipment is not the correct size.");

#endif // CUBE_EQUIPMENT_H
