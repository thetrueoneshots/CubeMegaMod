#include "math.h"
i64 pydiv(i64 a, i64 b) {
	i64 result = a / b;
	if ((a < 0) ^ (b < 0)) {
		if (pymod(a, b) != 0) {
			result -= 1;
		}
	}
	return result;
}

i64 pymod(i64 a, i64 b) {
	i64 result = a % b;
	if (result < 0) {
		result = b + result;
	}
	return result;
}
