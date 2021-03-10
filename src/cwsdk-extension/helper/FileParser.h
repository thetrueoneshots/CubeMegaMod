#pragma once

#include <vector>

class CubeMod;

namespace cube
{
	static auto SAVE_FOLDER = "Mods\\CubeMegaMod";
	static auto SAVE_FILE_NAME = "settings.cwb";

	void ApplySettings(std::vector<CubeMod*>* mods);
	void SaveSettings(std::vector<CubeMod*>* mods);
}