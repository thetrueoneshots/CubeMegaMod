#include "Equipment.h"

void cube::Equipment::Clear()
{
	cube::Item empty(0, 0);
	this->unk_item = empty;
	this->neck = empty;
	this->creature = empty;
	this->feet = empty;
	this->hands = empty;
	this->shoulder = empty;
	this->weapon_left = empty;
	this->weapon_right = empty;
	this->ring_left = empty;
	this->ring_right = empty;
	this->pet = empty;
}
