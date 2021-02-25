#include "Interaction.h"

cube::Interaction::Interaction(InteractionType type) {
	this->interaction_type = type;
}

void cube::Interaction::SetItem(const cube::Item& item) {
	this->item = item;
}