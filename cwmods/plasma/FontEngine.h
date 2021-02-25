#ifndef PLASMA_FONTENGINE_H
#define PLASMA_FONTENGINE_H

#include "../IDA/types.h"
#include <windows.h>
#include <string>

namespace plasma {
	class D3D11Engine;
	class ScalableFont;
    class FontEngine {
        public:
			virtual ~FontEngine();

			plasma::D3D11Engine* d3d11engine;
			__int64 field_10;
			__int64 field_18;
			__int64 field_20;
			__int64 field_28;
			__int64 field_30;
			__int64 field_38;
			__int64 field_40;
			CRITICAL_SECTION critical_section;


			plasma::ScalableFont* LoadFont(std::wstring* fileName);
        };
}

static_assert(sizeof(plasma::FontEngine) == 0x70, "plasma::FontEngine is not the correct size.");

#endif // PLASMA_FONTENGINE_H
