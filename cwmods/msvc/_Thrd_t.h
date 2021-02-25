#ifndef MSVC__THRD_T_H
#define MSVC__THRD_T_H

#include <windows.h>

namespace msvc {
    class _Thrd_t {
	public:
		uintptr_t _Hnd;
		unsigned int* _Id;
    };
}

#endif // MSVC__THRD_T_H
