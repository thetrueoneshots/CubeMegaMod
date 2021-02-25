#ifndef PLASMA_SCALABLEFONT_H
#define PLASMA_SCALABLEFONT_H

#include "../IDA/types.h"
#include <string>
#include "Windows.h"

namespace plasma {
	class D3D11Engine;
    class ScalableFont {
        public:
			virtual ~ScalableFont();

			plasma::D3D11Engine* d3d11engine;
			std::wstring wstring_0;
			std::wstring wstring_1;
			std::wstring wstring_2;
			std::wstring wstring_3;
			std::wstring field_90;
			__int64 field_B0;
			int field_B8;
			int field_BC;
			float field_C0;
			float field_C4;
			__int64 field_C8;
			int field_D0;
			float field_D4;
			float field_D8;
			int field_DC;
			__int64 field_E0;
			float field_E8;
			float field_EC;
			__int64 field_F0;
			int field_F8;
			float field_FC;
			__int64 field_100;
			__int64 field_108;
			__int64 field_110;
			__int64 field_118;
			__int64 field_120;
			__int64 field_128;
			__int64 field_130;
			__int64 field_138;
			__int64 field_140;
			__int64 field_148;
			__int64 field_150;
			__int64 field_158;
			char some_bool;
			CRITICAL_SECTION critical_section;
        };
}

static_assert(sizeof(plasma::ScalableFont) == 0x190, "plasma::ScalableFont is not the correct size.");

#endif // PLASMA_SCALABLEFONT_H
