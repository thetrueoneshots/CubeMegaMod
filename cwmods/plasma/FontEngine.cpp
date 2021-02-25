#include "FontEngine.h"
#include "../cwsdk.h"

plasma::ScalableFont* plasma::FontEngine::LoadFont(std::wstring* fileName) {
	return ((plasma::ScalableFont* (*)(plasma::FontEngine*, std::wstring*))CWOffset(0x34D060))(this, fileName);
}