#include "Speech.h"

#include "../cwsdk.h"

std::wstring* cube::Speech::GenerateItemName(std::wstring* string, cube::Item* item)
{
    return ((std::wstring* (*)(cube::Speech*, std::wstring*, cube::Item*))CWOffset(0x1628B0))(this, string, item);
}

std::wstring* cube::Speech::GetRaceName(std::wstring* str, int race)
{
    return ((std::wstring * (*)(cube::Speech*, std::wstring*, int))CWOffset(0x164760))(this, str, race);
}

