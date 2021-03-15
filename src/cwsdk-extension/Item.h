#pragma once
#include "cwsdk.h"

namespace cube
{
	inline bool CompareItemType(Item current, Item other)
	{
		return other.category == current.category && other.id == current.id;
	}

	namespace SpiritCube
	{
		enum class Type
		{
			FireSpirit = 128,
			UnholySpirit,
			IceSpirit,
			WindSpirit,
		};

		inline cube::Item Create(Type t = Type::FireSpirit)
		{
			cube::Item item(11, 14);
			item.material = (int)t;
			return item;
		}
	}
}