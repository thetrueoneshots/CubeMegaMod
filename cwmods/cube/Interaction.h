#ifndef CUBE_INTERACTION_H
#define CUBE_INTERACTION_H

#include "Interaction.h"
#include "Item.h"
#include "../common/Vector3.h"
#include "../common/types.h"

namespace cube {
class Interaction {
    public:
		enum InteractionType : u8 {
			Talk = 3,
			EndTalk = 4,
			StaticEntity = 5,
			Pickup = 7,
			Drop = 8,
			CallPet = 10
		};

		cube::Item item;
		IntVector3 position;
		int probably_padding_AC;
		__int64 creature_id_maybe;
		__int64 field_B8;
		int field_C0;
		InteractionType interaction_type;
		char padding_probably;
		__int16 field_C6;

		Interaction(InteractionType type);
		void SetItem(const cube::Item& item);
    };
}

static_assert(sizeof(cube::Interaction) == 0xC8, "cube::Interaction is not the correct size.");

#endif // CUBE_INTERACTION_H
