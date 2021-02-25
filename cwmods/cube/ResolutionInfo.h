#ifndef CUBE_RESOLUTIONINFO_H
#define CUBE_RESOLUTIONINFO_H

#include <map>
#include "../common/types.h"

namespace cube {
class ResolutionInfo {
    public:
		int width;
		int height;
		std::map<i32, i32> refresh_rates; //Keys are the available refresh rates, values are unknown.
    };
}

static_assert(sizeof(cube::ResolutionInfo) == 0x18, "cube::ResolutionInfo is not the correct size.");

#endif // CUBE_RESOLUTIONINFO_H
