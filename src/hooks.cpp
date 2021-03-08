#include "hooks.h"

// Include all hooks here.
#include "hooks/lore_increase.h"

/* Initializes all the needed mods.
 * @return	{void}
*/
void hook::InitializeAll(std::vector<HookEventData>* hookEvents)
{
	// Initialize all hooks here.
	//DropGoldOnHitInitialize();
	//ChestOpeningInitialize();
	IncreaseLoreInitialize(hookEvents);
}
