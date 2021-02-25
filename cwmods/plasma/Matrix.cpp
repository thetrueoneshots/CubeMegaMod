#include "Matrix.h"
#include <cmath>
#include <algorithm>

// based on http://www.songho.ca/opengl/gl_matrix.html


const float DEG2RAD = 3.141593f / 180.0f;
const float RAD2DEG = 180.0f / 3.141593f;
const float EPSILON = 0.00001f;

template<typename T>
plasma::Matrix<T>::Matrix(T m00, T m01, T m02, T m03, // 1st column
	T m04, T m05, T m06, T m07, // 2nd column
	T m08, T m09, T m10, T m11, // 3rd column
	T m12, T m13, T m14, T m15) // 4th column
{
	this->m[0] = m00; this->m[1] = m01; this->m[2] = m02; this->m[3] = m03;
	this->m[4] = m04; this->m[5] = m05; this->m[6] = m06; this->m[7] = m07;
	this->m[8] = m08; this->m[9] = m09; this->m[10] = m10; this->m[11] = m11;
	this->m[12] = m12; this->m[13] = m13; this->m[14] = m14; this->m[15] = m15;
}

//////////////////////////////////////////////////////////////////////////////
// operator overloads
//////////////////////////////////////////////////////////////////////////////
template<>
float plasma::Matrix<float>::operator[](int index) const
{
	return m[index];
}

template<>
float& plasma::Matrix<float>::operator[](int index)
{
	return m[index];
}

template<>
plasma::Matrix<float> plasma::Matrix<float>::operator+(const plasma::Matrix<float>& rhs) const
{
	return plasma::Matrix<float>(
		m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3],
		m[4] + rhs[4], m[5] + rhs[5], m[6] + rhs[6], m[7] + rhs[7],
		m[8] + rhs[8], m[9] + rhs[9], m[10] + rhs[10], m[11] + rhs[11],
		m[12] + rhs[12], m[13] + rhs[13], m[14] + rhs[14], m[15] + rhs[15]);
}

template<>
plasma::Matrix<float> plasma::Matrix<float>::operator-(const plasma::Matrix<float>& rhs) const
{
	return plasma::Matrix<float>(
		m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3],
		m[4] - rhs[4], m[5] - rhs[5], m[6] - rhs[6], m[7] - rhs[7],
		m[8] - rhs[8], m[9] - rhs[9], m[10] - rhs[10], m[11] - rhs[11],
		m[12] - rhs[12], m[13] - rhs[13], m[14] - rhs[14], m[15] - rhs[15]);
}

template<>
plasma::Matrix<float>& plasma::Matrix<float>::operator+=(const plasma::Matrix<float>& rhs)
{
	m[0] += rhs[0];   m[1] += rhs[1];   m[2] += rhs[2];   m[3] += rhs[3];
	m[4] += rhs[4];   m[5] += rhs[5];   m[6] += rhs[6];   m[7] += rhs[7];
	m[8] += rhs[8];   m[9] += rhs[9];   m[10] += rhs[10];  m[11] += rhs[11];
	m[12] += rhs[12];  m[13] += rhs[13];  m[14] += rhs[14];  m[15] += rhs[15];
	return *this;
}

template<>
plasma::Matrix<float>& plasma::Matrix<float>::operator-=(const plasma::Matrix<float>& rhs)
{
	m[0] -= rhs[0];   m[1] -= rhs[1];   m[2] -= rhs[2];   m[3] -= rhs[3];
	m[4] -= rhs[4];   m[5] -= rhs[5];   m[6] -= rhs[6];   m[7] -= rhs[7];
	m[8] -= rhs[8];   m[9] -= rhs[9];   m[10] -= rhs[10];  m[11] -= rhs[11];
	m[12] -= rhs[12];  m[13] -= rhs[13];  m[14] -= rhs[14];  m[15] -= rhs[15];
	return *this;
}

template<>
plasma::Matrix<float> plasma::Matrix<float>::operator*(const plasma::Matrix<float>& rhs) const
{
	return plasma::Matrix<float>(
		m[0] * rhs[0] + m[4] * rhs[1] + m[8] * rhs[2] + m[12] * rhs[3],
		m[1] * rhs[0] + m[5] * rhs[1] + m[9] * rhs[2] + m[13] * rhs[3],
		m[2] * rhs[0] + m[6] * rhs[1] + m[10] * rhs[2] + m[14] * rhs[3],
		m[3] * rhs[0] + m[7] * rhs[1] + m[11] * rhs[2] + m[15] * rhs[3],

		m[0] * rhs[4] + m[4] * rhs[5] + m[8] * rhs[6] + m[12] * rhs[7],
		m[1] * rhs[4] + m[5] * rhs[5] + m[9] * rhs[6] + m[13] * rhs[7],
		m[2] * rhs[4] + m[6] * rhs[5] + m[10] * rhs[6] + m[14] * rhs[7],
		m[3] * rhs[4] + m[7] * rhs[5] + m[11] * rhs[6] + m[15] * rhs[7],

		m[0] * rhs[8] + m[4] * rhs[9] + m[8] * rhs[10] + m[12] * rhs[11],
		m[1] * rhs[8] + m[5] * rhs[9] + m[9] * rhs[10] + m[13] * rhs[11],
		m[2] * rhs[8] + m[6] * rhs[9] + m[10] * rhs[10] + m[14] * rhs[11],
		m[3] * rhs[8] + m[7] * rhs[9] + m[11] * rhs[10] + m[15] * rhs[11],

		m[0] * rhs[12] + m[4] * rhs[13] + m[8] * rhs[14] + m[12] * rhs[15],
		m[1] * rhs[12] + m[5] * rhs[13] + m[9] * rhs[14] + m[13] * rhs[15],
		m[2] * rhs[12] + m[6] * rhs[13] + m[10] * rhs[14] + m[14] * rhs[15],
		m[3] * rhs[12] + m[7] * rhs[13] + m[11] * rhs[14] + m[15] * rhs[15]);
}

template<>
plasma::Matrix<float>& plasma::Matrix<float>::operator*=(const plasma::Matrix<float>& rhs)
{
	*this = *this * rhs;
	return *this;
}

template<>
bool plasma::Matrix<float>::operator==(const plasma::Matrix<float>& rhs) const
{
	return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) && (m[3] == rhs[3]) &&
		(m[4] == rhs[4]) && (m[5] == rhs[5]) && (m[6] == rhs[6]) && (m[7] == rhs[7]) &&
		(m[8] == rhs[8]) && (m[9] == rhs[9]) && (m[10] == rhs[10]) && (m[11] == rhs[11]) &&
		(m[12] == rhs[12]) && (m[13] == rhs[13]) && (m[14] == rhs[14]) && (m[15] == rhs[15]);
}

template<>
bool plasma::Matrix<float>::operator!=(const plasma::Matrix<float>& rhs) const
{
	return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) || (m[3] != rhs[3]) ||
		(m[4] != rhs[4]) || (m[5] != rhs[5]) || (m[6] != rhs[6]) || (m[7] != rhs[7]) ||
		(m[8] != rhs[8]) || (m[9] != rhs[9]) || (m[10] != rhs[10]) || (m[11] != rhs[11]) ||
		(m[12] != rhs[12]) || (m[13] != rhs[13]) || (m[14] != rhs[14]) || (m[15] != rhs[15]);
}

//template<>
//plasma::Matrix<float> operator-(const plasma::Matrix<float>& m)
//{
//	return plasma::Matrix<float>(-m[0], -m[1], -m[2], -m[3], -m[4], -m[5], -m[6], -m[7], -m[8], -m[9], -m[10], -m[11], -m[12], -m[13], -m[14], -m[15]);
//}

//template<>
//plasma::Matrix<float> operator*(float scalar, const plasma::Matrix<float>& m)
//{
//	float s = scalar;
//	return plasma::Matrix<float>(s * m[0], s * m[1], s * m[2], s * m[3], s * m[4], s * m[5], s * m[6], s * m[7], s * m[8], s * m[9], s * m[10], s * m[11], s * m[12], s * m[13], s * m[14], s * m[15]);
//}

//////////////////////////////////////////////////////////////////////////////
// scale only the x,y,z, factors
//////////////////////////////////////////////////////////////////////////////
template<>
plasma::Matrix<float>& plasma::Matrix<float>::scale(float x, float y, float z)
{
	m[0] *= x;   m[4] *= x;   m[8] *= x;
	m[1] *= y;   m[5] *= y;   m[9] *= y;
	m[2] *= z;   m[6] *= z;   m[10] *= z;
	return *this;
}


///////////////////////////////////////////////////////////////////////////////
// compute cofactor of 3x3 minor matrix without sign
// input params are 9 elements of the minor matrix
// NOTE: The caller must know its sign.
///////////////////////////////////////////////////////////////////////////////
template<>
float plasma::Matrix<float>::getCofactor(float m0, float m1, float m2,
	float m3, float m4, float m5,
	float m6, float m7, float m8) const
{
	return m0 * (m4 * m8 - m5 * m7) -
		m1 * (m3 * m8 - m5 * m6) +
		m2 * (m3 * m7 - m4 * m6);
}


///////////////////////////////////////////////////////////////////////////////
// transpose 4x4 matrix
///////////////////////////////////////////////////////////////////////////////
template<>
plasma::Matrix<float>& plasma::Matrix<float>::transpose()
{
	std::swap(m[1], m[4]);
	std::swap(m[2], m[8]);
	std::swap(m[3], m[12]);
	std::swap(m[6], m[9]);
	std::swap(m[7], m[13]);
	std::swap(m[11], m[14]);

	return *this;
}



///////////////////////////////////////////////////////////////////////////////
// compute the inverse of 4x4 Euclidean transformation matrix
//
// Euclidean transformation is translation, rotation, and reflection.
// With Euclidean transform, only the position and orientation of the object
// will be changed. Euclidean transform does not change the shape of an object
// (no scaling). Length and angle are reserved.
//
// Use inverseAffine() if the matrix has scale and shear transformation.
//
// M = [ R | T ]
//     [ --+-- ]    (R denotes 3x3 rotation/reflection matrix)
//     [ 0 | 1 ]    (T denotes 1x3 translation matrix)
//
// y = M*x  ->  y = R*x + T  ->  x = R^-1*(y - T)  ->  x = R^T*y - R^T*T
// (R is orthogonal,  R^-1 = R^T)
//
//  [ R | T ]-1    [ R^T | -R^T * T ]    (R denotes 3x3 rotation matrix)
//  [ --+-- ]   =  [ ----+--------- ]    (T denotes 1x3 translation)
//  [ 0 | 1 ]      [  0  |     1    ]    (R^T denotes R-transpose)
///////////////////////////////////////////////////////////////////////////////
template<>
plasma::Matrix<float>& plasma::Matrix<float>::invertEuclidean()
{
	// transpose 3x3 rotation matrix part
	// | R^T | 0 |
	// | ----+-- |
	// |  0  | 1 |
	float tmp;
	tmp = m[1];  m[1] = m[4];  m[4] = tmp;
	tmp = m[2];  m[2] = m[8];  m[8] = tmp;
	tmp = m[6];  m[6] = m[9];  m[9] = tmp;

	// compute translation part -R^T * T
	// | 0 | -R^T x |
	// | --+------- |
	// | 0 |   0    |
	float x = m[12];
	float y = m[13];
	float z = m[14];
	m[12] = -(m[0] * x + m[4] * y + m[8] * z);
	m[13] = -(m[1] * x + m[5] * y + m[9] * z);
	m[14] = -(m[2] * x + m[6] * y + m[10] * z);

	// last row should be unchanged (0,0,0,1)

	return *this;
}





///////////////////////////////////////////////////////////////////////////////
// return determinant of 4x4 matrix
///////////////////////////////////////////////////////////////////////////////
template<>
float plasma::Matrix<float>::getDeterminant() const
{
	return m[0] * getCofactor(m[5], m[6], m[7], m[9], m[10], m[11], m[13], m[14], m[15]) -
		m[1] * getCofactor(m[4], m[6], m[7], m[8], m[10], m[11], m[12], m[14], m[15]) +
		m[2] * getCofactor(m[4], m[5], m[7], m[8], m[9], m[11], m[12], m[13], m[15]) -
		m[3] * getCofactor(m[4], m[5], m[6], m[8], m[9], m[10], m[12], m[13], m[14]);
}





template<>
plasma::Matrix<float>& plasma::Matrix<float>::translate(float x, float y, float z)
{
	m[0] += m[3] * x;   m[4] += m[7] * x;   m[8] += m[11] * x;   m[12] += m[15] * x;
	m[1] += m[3] * y;   m[5] += m[7] * y;   m[9] += m[11] * y;   m[13] += m[15] * y;
	m[2] += m[3] * z;   m[6] += m[7] * z;   m[10] += m[11] * z;   m[14] += m[15] * z;

	return *this;
}



///////////////////////////////////////////////////////////////////////////////
// uniform scale
///////////////////////////////////////////////////////////////////////////////
template<>
plasma::Matrix<float>& plasma::Matrix<float>::scale(float s)
{
	return scale(s, s, s);
}




template<>
plasma::Matrix<float>& plasma::Matrix<float>::rotateX(float angle)
{
	float c = cosf(angle * DEG2RAD);
	float s = sinf(angle * DEG2RAD);
	float m1 = m[1], m2 = m[2],
		m5 = m[5], m6 = m[6],
		m9 = m[9], m10 = m[10];

	m[1] = m1 * c + m2 * -s;
	m[2] = m1 * s + m2 * c;
	m[5] = m5 * c + m6 * -s;
	m[6] = m5 * s + m6 * c;
	m[9] = m9 * c + m10 * -s;
	m[10] = m9 * s + m10 * c;

	return *this;
}

template<>
plasma::Matrix<float>& plasma::Matrix<float>::rotateY(float angle)
{
	float c = cosf(angle * DEG2RAD);
	float s = sinf(angle * DEG2RAD);
	float m0 = m[0], m2 = m[2],
		m4 = m[4], m6 = m[6],
		m8 = m[8], m10 = m[10];

	m[0] = m0 * c + m2 * s;
	m[2] = m0 * -s + m2 * c;
	m[4] = m4 * c + m6 * s;
	m[6] = m4 * -s + m6 * c;
	m[8] = m8 * c + m10 * s;
	m[10] = m8 * -s + m10 * c;

	return *this;
}

template<>
plasma::Matrix<float>& plasma::Matrix<float>::rotateZ(float angle)
{
	float c = cosf(angle * DEG2RAD);
	float s = sinf(angle * DEG2RAD);
	float m0 = m[0], m1 = m[1],
		m4 = m[4], m5 = m[5],
		m8 = m[8], m9 = m[9];

	m[0] = m0 * c + m1 * -s;
	m[1] = m0 * s + m1 * c;
	m[4] = m4 * c + m5 * -s;
	m[5] = m4 * s + m5 * c;
	m[8] = m8 * c + m9 * -s;
	m[9] = m8 * s + m9 * c;

	return *this;
}


