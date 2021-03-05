#include "FileParser.h"
#include <fstream>
#include <windows.h>
#include "cwsdk.h"

cube::FileVariables cube::ReadSettingsFile()
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
}
