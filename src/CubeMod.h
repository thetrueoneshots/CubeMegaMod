#pragma once

#include <string>
#include <fstream>

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
	char* m_FileName;
	int m_ID;
	ModVersion m_Version;
	bool m_Enabled;

	CubeMod() { 
		m_Name = "Standard Mod Class"; 
		m_FileName = "StandardModClass";
		m_ID = 0; 
		m_Version = { 1, 0, 0 }; 
		m_Enabled = true; 
	}

	/*
	* Triggers on interaction with chests created from a Creature.
	* 
	* @param	{cube::Game*}		game		Pointer to the game.
	* @param	{cube::Creature*}	creature	Pointer to the chest.
	* @param	{int}				type		Chest type [0-3].
	* @return	{int}							[1 -> open chest, 0 -> do not open chest]
	*/
	inline virtual int OnChestInteraction(cube::Game* game, cube::Creature* creature, int type) { return 0; }

	/*
	* Triggers on increase of lore.
	*
	* @param	{cube::Game*}		game		Pointer to the game.
	* @param	{int}				value		New percentage value of the lore.
	* @return	{void}
	*/
	inline virtual void OnLoreIncrease(cube::Game* game, int value) {}

	/*
	* Triggers on interaction with the shop
	*
	* @param	{cube::Game*}								game		Pointer to the game.
	* @param	{std::vector<cube::ItemStack>*}				itemVector	Pointer to the shop vector.
	* * @param	{int}										classType	Class of the shopkeeper interacted with.
	* @return	{void}
	*/
	inline virtual int OnShopInteraction(cube::Game* game, std::vector<std::vector<cube::ItemStack>>* itemVector, int classType, long long id) { return 0; }

	inline void Save(void* data, int size)
	{
		char fileName[256] = { 0 };

		CreateDirectory(cube::SAVE_FOLDER, NULL);
		sprintf(fileName, "%s\\%s.sav", cube::SAVE_FOLDER, m_FileName);

		std::ofstream file;
		file.open(fileName, std::ios::out | std::ios::binary);

		if (!file) {
			return;
		}

		// Write settings
		file.write((char*)data, sizeof(size));

		file.close();
	}
	
	inline void Load(void* data, int size)
	{
		char fileName[256] = { 0 };

		CreateDirectory(cube::SAVE_FOLDER, NULL);
		sprintf(fileName, "%s\\%s.sav", cube::SAVE_FOLDER, m_FileName);
		std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);

		if (!file.is_open()) {
			return;
		}

		//File exists, read it
		file.seekg(0, std::ios::beg);
		file.read((char*)data, sizeof(size));
		file.close();
	}
};