#ifndef INTVECTOR2_H
#define INTVECTOR2_H

#include <cstdint>
#include <iostream>

class IntVector2 {
    public:
        int x;
        int y;
        IntVector2(int x, int y);

		bool operator==(const IntVector2& other) const {
			return (this->x == other.x && this->y == other.y);
		}
    };

namespace std {
	template <>
	struct hash<IntVector2>
	{
		std::size_t operator()(const IntVector2& k) const
		{
			uint64_t x = (uint32_t)k.x;
			uint64_t y = (uint32_t)k.y;
			uint64_t key = x | (y << 32);

			// Call into the MSVC-STL FNV-1a std::hash function.
			return std::hash<uint64_t>()(key);
		}
	};
};


#endif // INTVECTOR2_H
