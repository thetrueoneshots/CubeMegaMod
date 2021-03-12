#include "Item.h"


cube::Item::Item(){
	ctor();
}
cube::Item::Item(char category, int id) {
	ctor();
    this->category = category;
	this->id = id;
}

void cube::Item::ctor()
{
	this->category = 0;
	this->id = 0;
	this->rarity = 0;
	this->modifier = 0;
	this->region = IntVector2(0, 0);
	this->material = 0;
	this->formula_category = 0;
	this->num_spirits = 0;

	for (int i = 0; i < 32; i++)
	{
		this->spirits[i] = { 0, 0, 0, 0 };
	}
}
