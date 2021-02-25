#ifndef HOST_H
#define HOST_H

#include "World.h"
#include "../msvc/_Thrd_t.h"
#include "../steam/steam_api_common.h"
#include "Connection.h"

namespace cube {
class Host {
    public:
		virtual ~Host();

		cube::World world;
		bool running;
		// 7 bytes padding
		msvc::_Thrd_t thread;
		std::map<CSteamID, cube::Connection*> connections;
		std::map<CSteamID, u32>  invitations; // value is time from timeGetTime()
		std::map<void*, void*> unk_list_0x588; // Node size 0x58
		std::map<void*, void*> unk_list_0x598; // Node size 0x40
		std::map<void*, void*> unk_list_0x5A8; // Node size 0x90
		std::map<void*, void*> unk_list_0x5B8; // Node size 0x40
		__int64 field_5C8;
		CRITICAL_SECTION host_recv_packet_list_lock;
		CRITICAL_SECTION cube_host_lock_1;
		std::list<void*> host_recv_packet_list;
    };
}

static_assert(sizeof(cube::Host) == 0x630, "cube::Host is not the correct size.");
#endif // HOST_H
