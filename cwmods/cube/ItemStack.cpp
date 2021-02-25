#include "ItemStack.h"
#include "Item.h"

cube::ItemStack::ItemStack() {
}
cube::ItemStack::ItemStack(int quantity, cube::Item item) {
    this->quantity = quantity;
    this->item = item;
}
