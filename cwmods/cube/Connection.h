#ifndef CUBE_CONNECTION_H
#define CUBE_CONNECTION_H

#include "../IDA/types.h"
#include "../steam/steam_api_common.h"
#include "ServerUpdates.h"

namespace cube {
class Connection {
    public:
		__int64 id;
		CSteamID steam_id;
		cube::ServerUpdates server_updates;
		__int64 field_110;
		__int64 field_118;
		__int64 field_120;
		__int64 field_128;
		__int64 field_130;
		__int64 field_138;
		__int64 some_0x998_sized_ptr;
		__int64 field_148;
    };
}

static_assert(sizeof(cube::Connection) == 0x150, "cube::Connection is not the correct size.");

#endif // CUBE_CONNECTION_H
