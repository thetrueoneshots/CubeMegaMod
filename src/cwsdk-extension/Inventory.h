#pragma once
#include <vector>
#include "cwsdk.h"

#include "Item.h"

namespace cube
{
	class Inventory
	{
	public:
		enum
		{
			EquipmentTab = 0,
			SpecialsTab,
			ItemsTab,
			IngredientsTab,
			PetsTab,
			ArtifactsTab
		};


		static bool ConsumeItem(const cube::Item& item, int count = 1, int tab = Inventory::IngredientsTab);
	};
}