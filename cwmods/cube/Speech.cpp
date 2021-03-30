#include "Speech.h"

#include "../cwsdk.h"

std::wstring* cube::Speech::GetItemName(std::wstring* string, cube::Item* item)
{
    return ((std::wstring* (*)(cube::Speech*, std::wstring*, cube::Item*))CWOffset(0x1628B0))(this, string, item);
}
