#pragma once

#include <cstdint>
#include <iostream>
#include "math.h"

template <typename T>
class Vector3 {
public:
	T x, y, z;
	Vector3() : x(0), y(0), z(0) {};
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {};

	bool operator==(const Vector3<T>& other) const {
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}


	// /
	Vector3<float> operator/(const Vector3<float>& other) const {
		return Vector3<float>(this->x / other.x, this->y / other.y, this->z / other.z);
	}
	Vector3<float> operator/(const float& other) const {
		return Vector3<float>(this->x / other, this->y / other, this->z / other);
	}

	Vector3<double> operator/(const Vector3<double>& other) const {
		return Vector3<double>(this->x / other.x, this->y / other.y, this->z / other.z);
	}
	Vector3<double> operator/(const double& other) const {
		return Vector3<double>(this->x / other, this->y / other, this->z / other);
	}

	Vector3<int> operator/(const Vector3<int>& other) const {
		return Vector3<int>(pydiv(this->x, other.x), pydiv(this->y, other.y), pydiv(this->z, other.z));
	}
	Vector3<int> operator/(const int& other) const {
		return Vector3<int>(pydiv(this->x, other), pydiv(this->y, other), pydiv(this->z, other));
	}

	Vector3<long long int> operator/(const Vector3<long long int>& other) const {
		return Vector3<long long int>(pydiv(this->x, other.x), pydiv(this->y, other.y), pydiv(this->z, other));
	}
	Vector3<long long int> operator/(long long int& other) const {
		return Vector3<long long int>(pydiv(this->x, other), pydiv(this->y, other), pydiv(this->z, other));
	}

	// %
	Vector3<float> operator%(const Vector3<float>& other) const {
		return Vector3<float>(this->x % other.x, this->y % other.y, this->z % other.z);
	}
	Vector3<float> operator%(const float& other) const {
		return Vector3<float>(this->x % other, this->y % other, this->z % other);
	}

	Vector3<double> operator%(const Vector3<double>& other) const {
		return Vector3<double>(this->x % other.x, this->y % other.y, this->z % other.z);
	}
	Vector3<double> operator%(const double& other) const {
		return Vector3<double>(this->x % other, this->y % other, this->z % other);
	}

	Vector3<int> operator%(const Vector3<int>& other) const {
		return Vector3<int>(pymod(this->x, other.x), pymod(this->y, other.y), pymod(this->z, other.z));
	}
	Vector3<int> operator%(const int& other) const {
		return Vector3<int>(pymod(this->x, other), pymod(this->y, other), pymod(this->z, other));
	}

	Vector3<long long int> operator%(const Vector3<long long int>& other) const {
		return Vector3<long long int>(pymod(this->x, other.x), pymod(this->y, other.y), pymod(this->z, other.z));
	}
	Vector3<long long int> operator%(long long int& other) const {
		return Vector3<long long int>(pymod(this->x, other), pymod(this->y, other), pymod(this->z, other));
	}

	// * 
	Vector3<T> operator*(const Vector3<T>& other) const {
		return Vector3<T>(this->x * other.x, this->y * other.y, this->z * other.z);
	}
	Vector3<T> operator*(const T& other) const {
		return Vector3<T>(this->x * other, this->y * other, this->z * other);
	}
};

typedef Vector3<int> IntVector3;
typedef Vector3<long long int> LongVector3;
typedef Vector3<float> FloatVector3;
typedef Vector3<double> DoubleVector3;