#pragma once

#include "cwsdk.h"

namespace cube
{
	namespace Enums
	{
		enum class EntityBehaviour
		{
			Player = 0,
			Hostile,
			Passive,
			NPC,
			NPCInteract,
			Unk_05,
			Pet,
			Inanimate,
			ExamineObject,
		};

		enum class CollisionFlags
		{
			Ground = 0,
			Water,
			Wall,
			Unk_03,
			Surfaced,
			Colliding,
			ClippingObject,
			Lava,
			Unk_08,
			Poison,
			Snow,
			Leaves,
			Unk_12,
			Unk_13,
			Unk_14,
			Unk_15,
		};

		enum class AppearanceModifiers
		{
			IsFourFooted = 0,
			Unk_01,
			Unk_02,
			Unk_03,
			Unk_04,
			Unk_05,
			IsClassMaster,
			Unk_07,
			Unk_08,
			IsNamedBoss,
			HasGlowingHair,
			Unk_11,
			Unk_12,
			IsNotTalking,
			CanPickup,
			IsFriendly,
			Unk_16,
			IsMiniBoss,
			IsBoss,
			Unk_19,
			IsGhost,
			IsUseable,
			IsPetrified,
			Unk_23,
			Unk_24,
			Unk_25,
			IsPossesed,
			Unk_27,
			Unk_28,
			Unk_29,
			Unk_30,
			Unk_31
		};

		enum class StateFlags
		{
			ActiveLantern = 0,
			Unk_01,
			Unk_02,
			Unk_03,
			Unk_04,
			Unk_05,
			IsRunning,
			Unk_07,
			VisibleOnMap,
			StayOnGround,
			IsSneaking,
			Unk_11,
			Unk_12,
			Unk_13,
			Unk_14,
			Unk_15
		};
	}
}