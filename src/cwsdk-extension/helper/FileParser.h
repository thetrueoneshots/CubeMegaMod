#pragma once

#include <vector>

class CubeMod;

namespace cube
{
	static auto SAVE_FOLDER = "Mods\\CubeMegaMod";
	static auto SAVE_FILE_NAME = "settings.cwb";

	struct FileVariables
	{
		bool m_DoubleTapActivated, m_AutomaticGoldConsumptionActivated;
	};

	void ApplySettings(std::vector<CubeMod*>* mods);
	void SaveSettings(std::vector<CubeMod*>* mods);
	//FileVariables ReadSettingsFile();
	//void WriteSettingsFile(const FileVariables& vars);
}