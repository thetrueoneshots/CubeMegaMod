#ifndef CUBE_PROJECTILE_H
#define CUBE_PROJECTILE_H

#include "../common/Vector3.h"
#include <stdint.h>

namespace cube {
class Projectile {
    public:
		enum ProjectileType : int32_t {
			Arrow = 0,
			Bullet = 1,
			Shuriken = 2,
			Light = 3,
			Fireball = 4,
			ArrowOrBoomerang = 5, // Boomerang if the projectile's GUID is valid creature and said creature has a boomerang equipped in the right weapon slot.
			Puddle = 6,
			IronDeposit = 7,
			Eagle = 8,
			Airship = 9,
			Medicine = 10,
		};

		enum ProjectileSubType : uint8_t {
			LavaPuddle = 1,
			HealingPuddle = 2,
			RangerUlt = 4,
			FireTrailPuddle = 5,
			PoisonPuddle = 6,
			HealingMedicine = 2,
			LavaMedicine = 1,
			PoisonMedicine = 6,
		};

		Projectile() {
			this->guid = (uint64_t)-1;
			this->some_size_in_blocks = 1.0;
			this->visual_size = 1.0;
			this->current_time_ms_float = 0.0;
			this->some_scalar_1 = 1.0;
			this->max_time_to_live_ms_int = 5000;
		}

		Projectile(const LongVector3& pos, int type, int subtype, int duration)
		{
			this->guid = (uint64_t)-1;
			this->pos = pos;
			this->target_pos = pos;
			this->field_38 = 1;
			this->field_3C = 1;
			this->field_40 = 1;
			this->velocity = FloatVector3();
			this->damage = 100.f;
			this->some_size_in_blocks = 5.f;
			this->visual_size = 1.f;
			this->some_scalar_1 = 1.0;
			this->field_60 = 1;
			this->field_64 = 1;
			this->projectile_type = (ProjectileType)type;
			this->projectile_subtype = subtype;
			this->current_time_ms_float = 0.f;
			this->max_time_to_live_ms_int = 5000;
			this->field_78 = 1;
			this->_pad = 0;
		}

		uint64_t guid;
		LongVector3 pos;
		LongVector3 target_pos;
		int32_t field_38;
		int32_t field_3C;
		int32_t field_40;
		FloatVector3 velocity;
		float damage;
		float some_size_in_blocks;
		float visual_size;
		float some_scalar_1;
		int32_t field_60;
		uint8_t field_64;
		ProjectileType projectile_type;
		uint8_t projectile_subtype; // 5 = fire trail
		float current_time_ms_float;
		int32_t max_time_to_live_ms_int;
		int32_t field_78;
		int32_t _pad;
    };
}

#endif // CUBE_PROJECTILE_H
