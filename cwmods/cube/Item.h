#ifndef ITEM_H
#define ITEM_H

#include "Spirit.h"
#include "../common/Vector2.h"

namespace cube {
class Creature;
class Item {
    public:
        char category;
		//3 bytes padding
        int id;
        unsigned int modifier;
        IntVector2 region;
        char rarity;
		//3 bytes padding
        int formula_category;
        char material;
        cube::Spirit spirits[32];
        char num_spirits;
		//2 bytes padding

        Item();
        Item(char category, int id);
        void ctor();


        void Copy(cube::Item* src);
        float GetArmor(cube::Creature* creature);
        float GetHP(cube::Creature* creature);
        int GetArtifactType();
        int GetEffectiveRarity(IntVector2* region);
        int GetPrice();
};
}

static_assert(sizeof(cube::Item) == 0xA0, "cube::Creature is not the correct size.");

#endif // ITEM_H
