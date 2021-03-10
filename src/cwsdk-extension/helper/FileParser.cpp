#include "FileParser.h"
#include <fstream>
#include <windows.h>
#include "cwsdk.h"

#include "../../CubeMod.h"

/*cube::FileVariables cube::ReadSettingsFile()
{
	char* blocks;
	std::streampos fsize;
	FileVariables vars = { false, true };

	char fileName[256] = { 0 };
	//const char* folderName = "Mods\\CubeMegaMod";

	CreateDirectory(SAVE_FOLDER, NULL);
	sprintf(fileName, "%s\\%s", SAVE_FOLDER, SAVE_FILE_NAME);//"settings.cwb");
	std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		return vars;
	}

	//File exists, read it
	fsize = file.tellg();
	blocks = new char[fsize];
	file.seekg(0, std::ios::beg);
	file.read(blocks, fsize);
	file.close();

	vars.m_DoubleTapActivated = (bool)blocks[0];
	vars.m_AutomaticGoldConsumptionActivated = (bool)blocks[1];

	delete[] blocks;

	return vars;
}

void cube::WriteSettingsFile(const FileVariables& vars)
{
	char fileName[256] = { 0 };
	//const char* folderName = "Mods\\Classes";

	CreateDirectory(SAVE_FOLDER, NULL);

	//File for this Zone
	sprintf(fileName, "%s\\%s", SAVE_FOLDER, SAVE_FILE_NAME);//"settings.cwb");
	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);

	if (!file) {
		return;
	}

	file.write((char*)&vars.m_DoubleTapActivated, sizeof(vars.m_DoubleTapActivated));
	file.write((char*)&vars.m_AutomaticGoldConsumptionActivated, sizeof(vars.m_AutomaticGoldConsumptionActivated));

	file.close();
}*/

struct ModSetting
{
	int ID;
	bool enabled;
};

// Todo: Implement
static void WriteModSetting(std::ofstream* file, const ModSetting& setting);
// Todo: Implement
static ModSetting ReadModSetting(std::ifstream* file)
{
	ModSetting setting;
	file->read((char*)&setting, sizeof(setting));
	return setting;
}

void cube::ApplySettings(std::vector<CubeMod*>* mods)
{
	std::vector<ModSetting> settings;
	char fileName[256] = { 0 };

	CreateDirectory(SAVE_FOLDER, NULL);
	sprintf(fileName, "%s\\%s", SAVE_FOLDER, SAVE_FILE_NAME);
	std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		return;
	}

	//File exists, read it
	file.seekg(0, std::ios::beg);
	int count;
	file.read((char*)&count, sizeof(count));
	for (int i = 0; i < count; i++)
	{
		settings.push_back(ReadModSetting(&file));
	}
	file.close();

	// Apply read settings
	for (CubeMod* mod : *mods)
	{
		for (ModSetting setting : settings)
		{
			if (setting.ID == mod->m_ID)
			{
				mod->m_Enabled = setting.enabled;
			}
		}
	}
}

void cube::SaveSettings(std::vector<CubeMod*>* mods)
{
	char fileName[256] = { 0 };

	CreateDirectory(SAVE_FOLDER, NULL);
	sprintf(fileName, "%s\\%s", SAVE_FOLDER, SAVE_FILE_NAME);
	std::ofstream file;
	file.open(fileName, std::ios::out | std::ios::binary);

	if (!file) {
		return;
	}

	// Write settings
	int size = mods->size();
	file.write((char*)&size, sizeof(size));
	for (CubeMod* mod : *mods)
	{
		ModSetting setting = { mod->m_ID, mod->m_Enabled };
		file.write((char*)&setting, sizeof(setting));
	}

	file.close();
}
