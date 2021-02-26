#ifndef CREATURE_H
#define CREATURE_H

#include "../IDA/types.h"
#include "../common/Vector3.h"
#include "../common/RGBA.h"
#include "../common/Matrix4.h"
#include <vector>
#include <list>
#include "ItemStack.h"
#include "Equipment.h"
#include "Interaction.h"
#include <windows.h>

namespace cube {
    class Creature {
	public:
        // cube::Creature::EntityData
        class EntityData {
		public:
            // cube::Creature::EntityData::Appearance
            class Appearance {
                public:
                __int16 field_78;
                ByteRGBA hair_color;
                char padding_7E;
                char padding_7F;
                unsigned int flags2;
                float graphics_scale;
                float hitbox_scale;
                float physics_scale;
                __int16 head_model;
                __int16 hair_model;
                __int16 hands_model;
                __int16 feet_model;
                __int16 chest_model;
                __int16 tail_model;
                __int16 shoulder_model;
                __int16 wings_model;
                float head_scale;
                float chest_scale;
                float hands_scale;
                float feet_scale;
                float unknown_scale;
                float weapon_scale;
                float tail_scale;
                float shoulder_scale;
                float wing_scale;
                float chest_rotation;
                FloatVector3 hands_rotation;
                float feet_rotation;
                float wings_rotation;
                float unknown_rotation;
                FloatVector3 chest_position;
                FloatVector3 head_position;
                FloatVector3 hands_position;
                FloatVector3 feet_position;
                FloatVector3 unknown_position;
                FloatVector3 wings_position;
            }; // end cube::Creature::EntityData::Appearance

			LongVector3 position;
			float pitch;
			float roll;
			float yaw;
			FloatVector3 velocity;
			FloatVector3 acceleration;
			FloatVector3 retreat;
			float head_rotation;
			unsigned int flags;
			char hostility_type;
			char field_61;
			char field_62;
			char field_63;
			unsigned int race;
			BYTE current_ability;
			char field_59;
			char field_5A;
			char field_5B;
			float time_since_ability;
			int hit_combo;
			float time_since_hit;
			cube::Creature::EntityData::Appearance appearance;
			__int16 binary_toggles;
			char field_11A;
			char field_11B;
			float roll_time;
			float stun_time;
			float unknown_time;
			float slowed_time;
			float sprint_time;
			int field_140;
			unsigned int level;
			int XP;
			unsigned __int8 classType;
			char specialization;
			// NEW
			_BYTE gap13E[2];
			IntVector2 current_region;
			// OLD: _BYTE gap13E[10];
			char charge;
			_BYTE gap149[27];
			FloatVector3 attack_rotation;
			float HP;
			float float_184;
			float MP;
			float stealth;
			_BYTE gap180[4];
			char field_184;
			_BYTE gap185[7];
			char interaction_state;
			_BYTE gap18D[59];
			cube::Item unk_item;
			cube::Equipment equipment;
			char name[16];
			__int64 field_958;
			char field_960;
			char field_961;
			char field_962;
			char field_963;
			int field_964;
			__int64 field_968;
        }; // end cube::Creature::EntityData

		class Buff { // start cube::Creature::Buff
		public:
			enum BuffType
			{
				AuraBulwark = 0x1,
				AuraWarFrenzy = 0x2,
				AuraCamouflage = 0x3,
				AuraPoisoned = 0x4,
				AuraManaShield = 0x6,
				AuraInstantFire = 0x9,
				AuraInstantShoot = 0xA,
				AuraDodge = 0xB,
				AuraSwiftness = 0xC,
				AuraNinjutsu = 0xD,
				AuraShadowClone = 0xF,
				AuraFlameRush = 0x10,
				AuraRegeneration = 0x11,
				AuraSpiritWorld = 0x13,
				AuraLifeFlask = 0x17,
				AuraArmorFlask = 0x18,
				AuraResistanceFlask = 0x19,
				AuraHeatResistance = 0x1A,
				AuraColdFlask = 0x1B,
				AuraPlagueResistance = 0x1C,
				AuraFrozen = 0x1D,
				AuraAncientPower = 0x21,
				AuraManaAbsorption = 0x22,
			};

		public:
			cube::Creature::Buff::BuffType type;
			float unk;
			float time_remaining;
			int32_t field_10;
			int32_t field_14;
			int32_t field_18;
		}; // end cube::Creature::Buff

		class AnimationState { // start cube::Creature::AnimationState
		public:
			cube::Creature* creature;
			int32_t current_animation_state_timer;
			int32_t current_animation_state_id;
			int32_t field_10;
			int32_t field_14;
			int64_t field_18;
			FloatVector3 left_hand_shifted_by;
			FloatVector3 right_hand_shifted_by;
			FloatVector3 left_hand_rot;
			FloatVector3 right_hand_rot;
			int64_t field_50;
			int64_t field_58;
			int64_t field_60;
			FloatVector3 body_rot;
			FloatVector3 entire_creature_rot;
			FloatVector3 body_shifted_by;
			FloatVector3 head_shifted_by;
			FloatVector3 head_rot;
			FloatVector3 something_that_rounds_to_360_multiples;
			float some_decreasing_timer_0;
			float some_hands_rot;
			float some_decreasing_timer_1;
			float some_body_with_feet_rot;
			FloatVector3 entire_creature_shifted_by;
			float some_feet_rot;
			int32_t field_D0;
			int32_t field_D4;
			int64_t face_sprite;
			int64_t hair_sprite;
			int64_t chest_sprite;
			int64_t unk_sprite;
			int64_t hands_sprite;
			int64_t wings_sprite;
			int64_t tail_sprite;
			int64_t feet_sprite;
			int64_t weapon_right_sprite;
			int64_t weapon_left_sprite;
			int64_t shoulder_sprite;
			int64_t neck_sprite;
			Matrix4 body_with_head_matrix;
			Matrix4 hands_matrix;
			Matrix4 body_matrix;
			Matrix4 head_matrix;
			Matrix4 hair_matrix;
			Matrix4 unk_matrix_278;
			Matrix4 unk_matrix_2B8;
			Matrix4 weapon_in_right_hand_matrix;
			Matrix4 weapon_in_left_hand_matrix;
			Matrix4 left_hand_matrix;
			Matrix4 right_hand_matrix;
			Matrix4 unk_matrix_3F8;
			Matrix4 unk_matrix_438;
			Matrix4 unk_matrix_478;
			Matrix4 unk_matrix_4B8;
			Matrix4 left_root_matrix;
			Matrix4 right_foot_matrix;
			Matrix4 field_578;
			Matrix4 field_5B8;
			Matrix4 field_5F8;
			Matrix4 field_638;
			Matrix4 field_678;
			Matrix4 field_6B8;
			Matrix4 field_6F8;
			Matrix4 field_738;
			Matrix4 field_778;
			Matrix4 field_7B8;
			Matrix4 field_7F8;
			Matrix4 field_838;
			Matrix4 field_878;
			int64_t field_8B8;
			int64_t field_8C0;
			uint8_t field_8C8;
			uint8_t field_8C9;
			uint8_t field_8CA;
			uint8_t field_8CB;
			int32_t field_8CC;
			int64_t field_8D0;
			int64_t field_8D8;
			int64_t field_8E0;
		}; // end cube::Creature::AnimationState


		// start cube::Creature
        public:
			void* vtable;
			__int64 id;
			cube::Creature::EntityData entity_data;
			std::list<cube::Creature::Buff> buffs;
			_BYTE gap990[16];
			float stamina;
			_BYTE gap9A4[76];
			std::vector<std::vector<cube::ItemStack>> inventory_tabs;
			int field_A08;
			cube::Item unk_item;
			int gold;
			_BYTE gapAB0[8];
			std::list<cube::Interaction> interactions;
			_BYTE gapAC8[144];
			int field_B58;
			int climbing_speed;
			int swimming_speed;
			int diving_skill;
			int riding_speed;
			int hang_gliding_speed;
			int sailing_speed;
			int lamp_diameter;
			_BYTE gapB78[184];
			__int64 field_C30;
			cube::Creature::AnimationState animation_state;
			_BYTE gap1520[215];
			char end;

            static cube::Creature* Create(__int64 id);
            cube::Creature* ctor(__int64* id);
			float GetArmor();
			float GetCritical(cube::Creature* other_creature = nullptr, bool other_creature_based_on_resistance = true);
			float GetAttackPower(bool unk_bool = true);
			float GetSpellPower(bool unk_bool = true);
			float GetHaste();
			float GetMaxHP();
			float GetResistance();
			float GetRegeneration();
			float GetManaGeneration();
    };
}

static_assert(sizeof(cube::Creature) == 0x15F8, "cube::Creature is not the correct size.");

#endif // CREATURE_H
