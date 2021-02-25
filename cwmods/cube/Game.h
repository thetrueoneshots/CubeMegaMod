#ifndef GAME_H
#define GAME_H

#include "../IDA/types.h"

#include "../msvc/_Thrd_t.h"

#include "Speech.h"
#include "World.h"
#include "Host.h"
#include "ChatWidget.h"
#include "WorldMap.h"
#include "../gfx/D3D11Renderer.h"
#include "Creature.h"
#include "Client.h"
#include "Controls.h"
#include "Database.h"
#include "Options.h"
#include "GUI.h"
#include "../common/Vector3.h"
#include "../common/Vector2.h"
#include "../common/Matrix4.h"
#include "Block.h"
#include "TextFX.h"

#include <string>
#include <map>

namespace cube {
    class Game {
        public:
            class CCallbackInternal_onP2PSessionRequest {
                public:
                    void *vtable;
                    __int64 field_8;
            };
			class KeyNames {
				public:
					std::map<uint32_t, std::wstring> key_full_names;
					std::map<uint32_t, std::wstring> key_abbreviated_names;
			};
			enum SoundEffect : u32
			{
				sound_hit = 0x0,
				sound_blade1 = 0x1,
				sound_blade2 = 0x2,
				sound_long_blade1 = 0x3,
				sound_long_blade2 = 0x4,
				sound_hit1 = 0x5,
				sound_hit2 = 0x6,
				sound_punch1 = 0x7,
				sound_punch2 = 0x8,
				sound_hit_arrow = 0x9,
				sound_hit_arrow_critical = 0xA,
				sound_smash1 = 0xB,
				sound_slam_ground = 0xC,
				sound_smash_hit2 = 0xD,
				sound_smash_jump = 0xE,
				sound_swing = 0xF,
				sound_shield_swing = 0x10,
				sound_swing_slow = 0x11,
				sound_swing_slow2 = 0x12,
				sound_arrow_destroy = 0x13,
				sound_blade1_0 = 0x14,
				sound_punch2_0 = 0x15,
				sound_salvo2 = 0x16,
				sound_sword_hit03 = 0x17,
				sound_block = 0x18,
				sound_shield_slam = 0x19,
				sound_roll = 0x1A,
				sound_destroy2 = 0x1B,
				sound_cry = 0x1C,
				sound_level_up = 0x1D,
				sound_skill_up = 0x1E,
				sound_quest_complete = 0x1F,
				sound_quest_progress = 0x20,
				sound_new_quest = 0x21,
				sound_water_splash01 = 0x22,
				sound_step2 = 0x23,
				sound_step_water = 0x24,
				sound_step_water2 = 0x25,
				sound_step_water3 = 0x26,
				sound_channel2 = 0x27,
				sound_channel_hit = 0x28,
				sound_fireball = 0x29,
				sound_fire_hit = 0x2A,
				sound_magic02 = 0x2B,
				sound_watersplash = 0x2C,
				sound_watersplash_hit = 0x2D,
				sound_lich_scream = 0x2E,
				sound_drink2 = 0x2F,
				sound_pickup = 0x30,
				sound_disenchant2 = 0x31,
				sound_upgrade2 = 0x32,
				sound_swirl = 0x33,
				sound_human_voice01 = 0x34,
				sound_human_voice02 = 0x35,
				sound_gate = 0x36,
				sound_spike_trap = 0x37,
				sound_fire_trap = 0x38,
				sound_lever = 0x39,
				sound_charge2 = 0x3A,
				sound_magic02_0 = 0x3B,
				sound_drop = 0x3C,
				sound_drop_coin = 0x3D,
				sound_drop_item = 0x3E,
				sound_male_groan = 0x3F,
				sound_female_groan = 0x40,
				sound_male_groan_0 = 0x41,
				sound_female_groan_0 = 0x42,
				sound_goblin_male_groan = 0x43,
				sound_goblin_female_groan = 0x44,
				sound_lizard_male_groan = 0x45,
				sound_lizard_female_groan = 0x46,
				sound_dwarf_male_groan = 0x47,
				sound_dwarf_female_groan = 0x48,
				sound_orc_male_groan = 0x49,
				sound_orc_female_groan = 0x4A,
				sound_undead_male_groan = 0x4B,
				sound_undead_female_groan = 0x4C,
				sound_frogman_male_groan = 0x4D,
				sound_frogman_female_groan = 0x4E,
				sound_monster_groan = 0x4F,
				sound_troll_groan = 0x50,
				sound_mole_groan = 0x51,
				sound_slime_groan = 0x52,
				sound_zombie_groan = 0x53,
				sound_Explosion = 0x54,
				sound_punch2_1 = 0x55,
				sound_menu_open2 = 0x56,
				sound_menu_close2 = 0x57,
				sound_menu_select = 0x58,
				sound_menu_tab = 0x59,
				sound_menu_grab_item = 0x5A,
				sound_menu_drop_item = 0x5B,
				sound_craft = 0x5C,
				sound_craft_proc = 0x5D,
				sound_absorb = 0x5E,
				sound_manashield = 0x5F,
				sound_bulwark = 0x60,
				sound_bird1 = 0x61,
				sound_bird2 = 0x62,
				sound_bird3 = 0x63,
				sound_cricket1 = 0x64,
				sound_cricket2 = 0x65,
				sound_owl1 = 0x66,
				sound_owl2 = 0x67,
				sound_river1 = 0x68,
				sound_river2 = 0x69,
				sound_river3 = 0x6A,
				sound_heroic_shout = 0x6B,
				sound_machine = 0x6C,
				sound_flute1 = 0x6D,
				sound_flute2 = 0x6E,
				sound_harp1 = 0x6F,
				sound_harp2 = 0x70,
				sound_fiddle1 = 0x71,
				sound_whistle1 = 0x72,
				sound_whistle2 = 0x73,
				sound_bell1 = 0x74,
				sound_bell2 = 0x75,
				sound_lute1 = 0x76,
				sound_nightingale1 = 0x77,
				sound_wind = 0x78,
				sound_eagle = 0x79,
				sound_speech_end = 0x7A,
				sound_speech_next = 0x7B,
				sound_tamers_whistle = 0x7C,
			};
			
			virtual ~Game();

			cube::World* world;
			cube::WorldMap* worldmap;
			gfx::D3D11Renderer* renderer;
			plasma::D3D11Engine* plasma_engine;
			__int64 xaudio2_engine;
			cube::Game::KeyNames key_info;
			cube::Speech speech;
			cube::GUI gui;
			cube::Host host;
			cube::Client client;
			__int64 field_1770;
			std::vector<cube::Creature*> saved_characters;
			__int64 field_1790;
			__int64 field_1798;
			__int64 field_17A0;
			std::vector<std::vector<cube::ItemStack>> crafting_menu_tabs;
			__int64 field_17C0;
			_BYTE gap17C8[408];
			cube::Game::CCallbackInternal_onP2PSessionRequest onP2PSessionRequest_callback;
			_BYTE gap1970[256];
			bool control_states[23];
			bool vk_states[256];
			char field_1B87;
			cube::Options options;
			cube::Controls controls;
			int pad_1C94;
			CRITICAL_SECTION critical_section_0;
			CRITICAL_SECTION critical_section_1;
			CRITICAL_SECTION critical_section_2;
			CRITICAL_SECTION critical_section_3;
			CRITICAL_SECTION critical_section_4;
			int width;
			int height;
			_BYTE gap1D68[24];
			DoubleVector3 camera_angle;
			DoubleVector3 target_camera_angle;
			int field_1DB0;
			float camera_distance;
			float target_camera_distance;
			int field_1DBC;
			LongVector3 global_camera_position;
			LongVector3 global_camera_focus_position;
			__int64 negative_camera_focus_x;
			__int64 negative_camera_focus_y;
			float screen_shake;
			int map_zoom;
			LongVector3 map_position_weird;
			LongVector3 map_position;
			bool map_zoom_has_changed;
			char field_1E39;
			char field_1E3A;
			char field_1E3B;
			char field_1E3C;
			char field_1E3D;
			char field_1E3E;
			char field_1E3F;
			__int64 field_1E40;
			FloatVector2 map_overlay_position;
			float map_overlay_scale;
			_BYTE gap1E54[28];
			int usually_max_int_0;
			int usually_max_int_1;
			int usually_max_int_2;
			int usually_max_int_3;
			int usually_max_int_4;
			int field_1E84;
			bool looking_at_creature;
			char field_1E89;
			char field_1E8A;
			char field_1E8B;
			int field_1E8C;
			int field_1E90;
			int field_1E94;
			int field_1E98;
			int field_1E9C;
			int field_1EA0;
			Matrix4 some_camera_matrix_0;
			Matrix4 some_camera_matrix_1;
			Matrix4 some_camera_matrix_2;
			Matrix4 some_camera_matrix_3;
			int field_1FA4;
			msvc::_Thrd_t generation_thread;
			msvc::_Thrd_t chunk_thread;
			msvc::_Thrd_t map_thread;
			msvc::_Thrd_t ai_thread;
			msvc::_Thrd_t music_thread;
			msvc::_Thrd_t receive_thread;
			msvc::_Thrd_t send_thread;
			msvc::_Thrd_t host_thread;
			std::string* current_music_file;
			_BYTE gap2030[24];
			float music_volume;
			_BYTE gap204C[32];
			int seed;
			std::string world_name;
			__int16 gap2070;
			_BYTE gap2092[30];
			std::list<cube::TextFX> textfx_list;
			__int64 field_20C0;
			float field_20C8;
			float crafting_progress;
			float crafting_speed;
			int field_20D4;
			cube::Item crafting_item;
			_BYTE gap2178[236];
			int current_character_slot;
			cube::Database characters_db;
			cube::Database database_1;


            cube::Creature* GetPlayer();
			bool cube::Game::TraceCrosshairToBlock(float reach_in_blocks_from_camera, bool want_face_block, LongVector3* result, bool pass_through_water=false);
            void PrintMessage(const wchar_t* message, FloatRGBA* color);
            void PrintMessage(const wchar_t* message);
            void PrintMessage(const wchar_t* message, char red, char green, char blue);
			void PlaySoundEffect(SoundEffect sound_id, LongVector3& position, float volume=1.0, float speed=1.0, bool unkbool=true);
			void PlaySoundEffect(SoundEffect sound_id, float volume = 1.0, float speed = 1.0, bool unkbool = true);
        };
}

static_assert(sizeof(cube::Game) == 0x2288, "cube::Game is not the correct size.");

#endif // GAME_H
