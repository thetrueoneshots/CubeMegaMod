#ifndef ITEMSTACK_H
#define ITEMSTACK_H

#include "Item.h"

namespace cube {
class ItemStack {
    public:
        int quantity;
        cube::Item item;

        ItemStack();
        ItemStack(int quantity, cube::Item item);
    };
}

#endif // ITEMSTACK_H
