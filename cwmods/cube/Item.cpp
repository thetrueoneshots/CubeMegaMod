#include "Item.h"
#include "cwsdk.h"

cube::Item::Item(){
	ctor();
}
cube::Item::Item(char category, int id) {
	ctor();
    this->category = category;
	this->id = id;
}

void cube::Item::Copy(cube::Item* src)
{
	((void(*)(cube::Item*, cube::Item*))CWOffset(0x9CD0))(this, src);
}

float cube::Item::GetArmor(cube::Creature* creature)
{
	return ((float (*)(cube::Item*, cube::Creature*))CWOffset(0x108D50))(this, creature);
}

float cube::Item::GetHP(cube::Creature* creature)
{
	return ((float (*)(cube::Item*, cube::Creature*))CWOffset(0x1097B0))(this, creature);
}

int cube::Item::GetArtifactType()
{
	return ((int (*)(cube::Item*))CWOffset(0x108D50))(this);
}

int cube::Item::GetEffectiveRarity(IntVector2* region)
{
	return ((int (*)(cube::Item*, IntVector2*))CWOffset(0x109720))(this, region);
}

int cube::Item::GetPrice()
{
	return ((int (*)(cube::Item*))CWOffset(0x109D30))(this);
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
