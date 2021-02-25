#include "Inventory.h"

bool cube::Inventory::ConsumeItem(const cube::Item& item, int count, int tab)
{
	if (tab > Inventory::ArtifactsTab)
	{
		return false;
	}

	cube::Creature* player = cube::GetGame()->GetPlayer();
	for (int i = 0; i < player->inventory_tabs.at(tab).size(); i++)
	{
		cube::ItemStack* stack = &player->inventory_tabs.at(tab).at(i);
		if (cube::CompareItemType(stack->item, item) && stack->quantity >= count)
		{
			stack->quantity -= count;
			if (stack->quantity <= 0)
			{
				player->inventory_tabs.at(tab).erase(player->inventory_tabs.at(tab).begin() + i);
			}
			return true;
		}
	}
	return false;
}
