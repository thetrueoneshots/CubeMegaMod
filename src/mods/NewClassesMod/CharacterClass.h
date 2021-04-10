#pragma once
#include <string>
#include "cwsdk.h"

/*
* Todo: 
* - Specialization names
* - Modify the available races
* - Adding ones own abilities
*/

class CharacterClass
{
public:
	char* m_Name;
	wchar_t* m_WideName;

	enum ManaGenerationType : int
	{
		PassiveManaLoss = 0,
		PassiveManaGain,
		NoManaChange
	};

	CharacterClass(char* name, wchar_t* widename) : m_Name(name), m_WideName(widename) {};
	~CharacterClass() {};
	
	/*
	* Called when the starter gear of the class is generated. Anything can be added to the player at this point.
	* (Although gold might be kept to 40 with the beginner mode).
	* 
	* @param	{cube::Game*}		game	Pointer to the game.
	* @param	{cube::Creature*}	player	Pointer to the player.
	* @return	{void}
	*/
	inline virtual void GenerateStarterGear(cube::Game* game, cube::Creature* player) {}

	/*
	* Returns the ID of the ability to be used for the ultimate ability.
	* Note that with the player passed as parameter, you can check for resources,
	* current abilities and more.
	* Note to be careful with floats. Printing in the chat causes a crash, because xmm registers are changed when using floats.
	*
	* @param	{cube::Creature*}	player	Pointer to the player.
	* @return	{int}						Ability ID in CW.
	*/
	inline virtual int GetUltimateAbilityId(cube::Creature* player) { return 0; }

	/*
	* Returns the cooldown of the ability. This can be depending on the specialization, specific abilityID or
	* just do it for the whole character at once. That is all okay.
	* 
	* @param	{cube::Creature*}	player		Pointer to the player.
	* @param	{int}				abilityID	ID of the ability the cooldown is needed for.
	* @return	{int}							Cooldown in milliseconds. (1000 is one second)
	*/
	inline virtual int GetUltimateAbilityCooldown(cube::Creature* player, int abilityID) { return 0; }

	/*
	* Returns the ID of the ability to be used for the shift ability.
	* Note that with the player passed as parameter, you can check for resources,
	* current abilities and more.
	* Note to be careful with floats. Printing in the chat causes a crash, because xmm registers are changed when using floats.
	*
	* @param	{cube::Creature*}	player	Pointer to the player.
	* @return	{int}						Ability ID in CW.
	*/
	inline virtual int GetShiftAbilityId(cube::Creature* player) { return 0; }

	/*
	* Returns the ID of the ability to be used for the middle mouse button.
	* Note that with the player passed as parameter, you can check for resources,
	* current abilities and more.
	* Note to be careful with floats. Printing in the chat causes a crash, because xmm registers are changed when using floats.
	* 
	* @param	{cube::Creature*}	player	Pointer to the player.
	* @return	{int}						Ability ID in CW.
	*/
	inline virtual int GetMiddleMouseAbilityId(cube::Creature * player) { return 0; }

	/*
	* Function to check if a certain item can be equipped by this character.
	* Do note that there is no access here to the player as a parameter, but this can 
	* be done by calling cube::GetGame()->GetPlayer() possibly.
	* 
	* @param	{cube::Item*}	item	Pointer to the item.
	* @return	{bool}					If the item can be equipped.
	*/
	inline virtual bool CanEquipItem(cube::Item* item) { return true; }
	
	/*
	* What type of mana generation the character should have.
	* Returning 0: Passive mana loss
	*			1: Passive mana gain
	*			2: No passive mana change
	* Note to be careful with floats. Printing in the chat causes a crash, because xmm registers are changed when using floats.
	* 
	* @param	{cube::Creature*}	player	Pointer to the player
	* @return	{int}						Mana generation type
	*/
	inline virtual int ManaGenerationType(cube::Creature* player) { return 0; }

	/*
	* What type of class the treasure items should have for this character.
	* Returning 0: Random Roulette
	*			1: Warrior
	*			2: Ranger
	*			3: Mage
	*			4: Rogue
	* Note to be careful with floats. Printing in the chat causes a crash, because xmm registers are changed when using floats.
	* 
	* @param	{cube::Creature*}	player	Pointer to the player
	* @return	{int}						Treasure class type
	*/
	inline virtual int GetTreasureClassType(cube::Creature* player) { return 0; }

	/*
	* Called on initialization of the classes. This is when the first game tick happens.
	* Ability names, specialization names and other initalization things can be done here.
	*
	* @param	{cube::Game*}		game	Pointer to the game.
	* @return	{void}
	*/
	inline virtual void Initialize(cube::Game* game) {}

};