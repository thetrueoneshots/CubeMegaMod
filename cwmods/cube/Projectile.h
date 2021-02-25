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
			unk3 = 3,
			Fireball = 4,
			ArrowOrBoomerang = 5, // Boomerang if the projectile's GUID is valid creature and said creature has a boomerang equipped in the right weapon slot.
			unk6 = 6,
			IronDeposit = 7,
			Eagle = 8,
			Airship = 9,
			Medicine = 10,
		};

		Projectile() {
			guid = (uint64_t)-1;
			some_size_in_blocks = 1.0;
			visual_size = 1.0;
			current_time_ms_float = 0.0;
			some_scalar_1 = 1.0;
			max_time_to_live_ms_int = 5000;
		}

		uint64_t guid;
		LongVector3 pos;
		LongVector3 unk_pos;
		int32_t field_38;
		int32_t field_3C;
		int32_t field_40;
		FloatVector3 velocity;
		float field_50;
		float some_size_in_blocks;
		float visual_size;
		float some_scalar_1;
		int32_t field_60;
		uint8_t field_64;
		ProjectileType projectile_type;
		uint8_t field_6C;
		float current_time_ms_float;
		int32_t max_time_to_live_ms_int;
		int32_t field_78;
		int32_t _pad;
    };
}

#endif // CUBE_PROJECTILE_H
