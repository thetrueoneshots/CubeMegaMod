#ifndef CUBE_BLOCKPROPERTIES_H
#define CUBE_BLOCKPROPERTIES_H
#include "../common/types.h"
#include "../IDA/types.h"

namespace cube {
template <typename T>
class BlockProperties {
    public:
		enum Type : u8 {
			Air        = 0,
			Solid      = 1,
			Water      = 2,
			Wet        = 3,
			Grass      = 4,
			Ground     = 5,
			Building   = 6,
			Tree       = 7,
			Leaves     = 8,
					   
			Snow       = 10,
			SnowLeaves = 11,

			Path       = 13,
					   
			Lava       = 17,
			Cave       = 18,
			Poison     = 19,
		};

		T red;
		T green;
		T blue;
		u8 field_3;
		Type type;
		u8 breakable;
		
		template <typename T2>
		void Half(BlockProperties<T2>& other) {
			red = other.red / (T2)2;
			green = other.green / (T2)2;
			blue = other.blue / (T2)2;

			for (T* color : { &red, &green, &blue }) {
				if (*color > (T)255) *color = (T)255;
				else if (*color < (T)0) *color = (T)0;
			}

			return;
		}
    };
}
#endif // CUBE_BLOCKPROPERTIES_H
