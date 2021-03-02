#include "hooks.h"

// Include all hooks here.
#include "hooks/drop_gold_on_hit.h"
#include "hooks/chest_opening.h"
#include "hooks/lore_increase.h"

/* Initializes all the needed mods.
 * @return	{void}
*/
void hook::InitializeAll(std::vector<HookEvent>* hookEvents)
{
	// Initialize all hooks here.
	//DropGoldOnHitInitialize();
	ChestOpeningInitialize();
	IncreaseLoreInitialize(hookEvents);
}

void hook::DisableCreatureFloating()
{
	WriteByte(CWOffset(0x2BF67A), 0xEB);
}

void hook::EnableCreatureFloating()
{
	WriteByte(CWOffset(0x2BF67A), 0xFF);
}
