#pragma once

#include "../IDA/types.h"
#include "../common/RGBA.h"

namespace cube 
{
	class SaveData 
	{
	public:
		int race;
		char gender;
		// 3 bytes padding
		int face;
		int haircut;
		ByteRGBA hair_color;
	};
}