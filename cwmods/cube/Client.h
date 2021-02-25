#ifndef CLIENT_H
#define CLIENT_H

#include "../IDA/types.h"
#include "../msvc/_Thrd_t.h"
#include <windows.h>
#include <list>
#include <map>
#include "Creature.h"
#include "../steam/steam_api_common.h"
#include "../common/BytesIO.h"

namespace cube {
	class Host;
	class Game;
    class Client {
        public:
			virtual ~Client();

			char running_callbacks;
			char pad_9;
			char pad_A;
			char pad_B;
			int field_C;
			msvc::_Thrd_t thread;
			std::list<void*> some_list_sent_as_SC_PACKET_0x0A;
			std::list<void*> some_list_sent_as_SC_PACKET_0x0B;
			std::list<void*> some_list_sent_as_SC_PACKET_0x0C;
			std::list<void*> some_list_sent_as_SC_PACKET_0x0D;
			std::list<void*> some_list_unk;
			CSteamID host_steam_id;
			cube::Creature::EntityData local_entity_data;
			int field_9E8;
			int unk_timestamp_after_sending_packets;
			std::map<void*, void*> some_recv_creatures_map;
			std::map<void*, void*> invited_by_map_maybe;
			cube::Host* host;
			CRITICAL_SECTION client_recv_packet_list_lock;
			std::list<std::pair<CSteamID, BytesIO*>> client_recv_packet_list;
			cube::Game* game;

            void JoinSteamID(long long steamID);
        };
}
static_assert(sizeof(cube::Client) == 0xA58, "cube::Client is not the correct size.");
#endif // CLIENT_H
