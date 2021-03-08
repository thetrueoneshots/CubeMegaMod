#pragma once
#include <string>

#include "cwsdk.h"

#include "cwsdk-extension.h"
#include "hooks.h"

/*
* Structure for defining the version of a mod.
*/
struct ModVersion
{
	int major, minor, sub;
	ModVersion() { this->major = 1; this->minor = 0; this->sub = 0; }
	ModVersion(int major, int minor, int sub) { this->major = major; this->minor = minor; this->sub = sub; }
	std::string ToString()
	{
		return "v" + std::to_string(this->major) + "." + std::to_string(this->minor) + "." + std::to_string(this->sub);
	}
};

/*
* Extended version of the GenericMod from the CWSDK.
*/
class CubeMod : public GenericMod
{
public:
	std::string m_Name;
	ModVersion m_Version;

	/*
	* Triggers on interaction with chests created from a Creature.
	* 
	* @param	{cube::Game*}		game		Pointer to the game.
	* @param	{cube::Creature*}	creature	Pointer to the chest.
	* @param	{int}				type		Chest type [0-3].
	* @return	{int}							[1 -> open chest, 0 -> do not open chest]
	*/
	inline virtual int OnChestInteraction(cube::Game* game, cube::Creature* creature, int type) { return 0; };

	/*
	* Triggers on increase of lore.
	*
	* @param	{int}				percentage	New percentage of the lore.
	* @return	{void}
	*/
	inline virtual void OnLoreIncrease(int percentage) {};
};