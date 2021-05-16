#include "StackUpdatesMod.h"

void StackUpdatesMod::Initialize()
{
	auto offset_p1 = 0x50755;	// Ensure all stack sizes are the same.
	auto offset_p2 = 0x50789;	// Increase all stack sizes.

	WriteByte(CWOffset(offset_p1), 0xEB);		// Change 0x75 (jne / jnz) to 0xEB (jmp). Always takes the big stack size.
	WriteByte(CWOffset(offset_p2 + 3), 0x64);	// Change 0x32 (50) to 0x64 (100). Increases the stack sizes to 100.
}
