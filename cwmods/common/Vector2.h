#pragma once

#include <cstdint>
#include <iostream>
#include "math.h"

template <typename T>
class Vector2 {
    public:
		T x, y;
		Vector2() : x(0), y(0) {};
		Vector2(T x, T y) : x(x), y(y) {};

		bool operator==(const Vector2<T>& other) const {
			return (this->x == other.x && this->y == other.y);
		}

		Vector2<float> operator/(const Vector2<float>& other) const {
			return Vector2<float>(this->x / other.x, this->y / other.y);
		}
		Vector2<float> operator/(const float& other) const {
			return Vector2<float>(this->x / other, this->y / other);
		}

		Vector2<double> operator/(const Vector2<double>& other) const {
			return Vector2<double>(this->x / other.x, this->y / other.y);
		}
		Vector2<double> operator/(const double& other) const {
			return Vector2<double>(this->x / other, this->y / other);
		}

		Vector2<int> operator/(const Vector2<int>& other) const {
			return Vector2<int>(pydiv(this->x, other.x), pydiv(this->y, other.y));
		}
		Vector2<int> operator/(const int& other) const {
			return Vector2<int>(pydiv(this->x, other), pydiv(this->y, other));
		}

		Vector2<long long int> operator/(const Vector2<long long int>& other) const {
			return Vector2<long long int>(pydiv(this->x, other.x), pydiv(this->y, other.y));
		}
		Vector2<long long int> operator/(long long int& other) const {
			return Vector2<long long int>(pydiv(this->x, other), pydiv(this->y, other));
		}
    };

namespace std {
	template <>
	struct hash<Vector2<int>>
	{
		std::size_t operator()(const Vector2<int>& k) const
		{
			uint64_t x = (uint32_t)k.x;
			uint64_t y = (uint32_t)k.y;
			uint64_t key = x | (y << 32);

			// Call into the MSVC-STL FNV-1a std::hash function.
			return std::hash<uint64_t>()(key);
		}
	};
};

typedef Vector2<int> IntVector2;
typedef Vector2<long long int> LongVector2;
typedef Vector2<float> FloatVector2;