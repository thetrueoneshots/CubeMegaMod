#pragma once

namespace cube
{
	static auto SAVE_FOLDER = "Mods\\CubeMegaMod";
	static auto SAVE_FILE_NAME = "settings.cwb";

	struct FileVariables
	{
		bool m_DoubleTapActivated, m_AutomaticGoldConsumptionActivated;
	};

	FileVariables ReadSettingsFile();
	void WriteSettingsFile(const FileVariables& vars);
}