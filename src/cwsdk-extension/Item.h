#pragma once
#include "cwsdk.h"

namespace cube
{
	inline bool CompareItemType(Item current, Item other)
	{
		return other.category == current.category && other.id == current.id;
	}
}