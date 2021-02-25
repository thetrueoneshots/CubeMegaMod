#ifndef PLASMA_MATRIX_H
#define PLASMA_MATRIX_H

// based on http://www.songho.ca/opengl/gl_matrix.html

#include <ostream>

namespace plasma {
	//This class has a template, but really it's only implemented for float
	//It only has a template to match RTTI information
	template <typename T>
	class Matrix
	{
	public:
		// constructors
		Matrix();  // init with identity
		Matrix(const T src[16]);
		Matrix(T m00, T m01, T m02, T m03, // 1st column
			T m04, T m05, T m06, T m07, // 2nd column
			T m08, T m09, T m10, T m11, // 3rd column
			T m12, T m13, T m14, T m15);// 4th column

		void        set(const float src[16]);
		void        set(float m00, float m01, float m02, float m03, // 1st column
			float m04, float m05, float m06, float m07, // 2nd column
			float m08, float m09, float m10, float m11, // 3rd column
			float m12, float m13, float m14, float m15);// 4th column
		void        setRow(int index, const float row[4]);

		const float* get() const;
		const float* getfloatranspose();                        // return transposed matrix
		float       getDeterminant() const;

		Matrix& identity();
		Matrix& transpose();                            // transpose itself and return reference
		Matrix& invert();                               // check best inverse method before inverse
		Matrix& invertEuclidean();                      // inverse of Euclidean transform matrix
		Matrix& invertAffine();                         // inverse of affine transform matrix
		Matrix& invertProjective();                     // inverse of projective matrix using partitioning
		Matrix& invertGeneral();                        // inverse of generic matrix

		// transform matrix
		Matrix& translate(float x, float y, float z);   // translation by (x,y,z)
		Matrix& rotate(float angle, float x, float y, float z);
		Matrix& rotateX(float angle);                   // rotate on X-axis with degree
		Matrix& rotateY(float angle);                   // rotate on Y-axis with degree
		Matrix& rotateZ(float angle);                   // rotate on Z-axis with degree
		Matrix& scale(float scale);                     // uniform scale
		Matrix& scale(float sx, float sy, float sz);    // scale by (sx, sy, sz) on each axis
		Matrix& lookAt(float tx, float ty, float tz);   // face object to the target direction
		Matrix& lookAt(float tx, float ty, float tz, float ux, float uy, float uz);

		// operators
		Matrix     operator+(const Matrix& rhs) const;    // add rhs
		Matrix     operator-(const Matrix& rhs) const;    // subtract rhs
		Matrix& operator+=(const Matrix& rhs);         // add rhs and update this object
		Matrix& operator-=(const Matrix& rhs);         // subtract rhs and update this object
		Matrix     operator*(const Matrix& rhs) const;    // multiplication: M3 = M1 * M2
		Matrix& operator*=(const Matrix& rhs);         // multiplication: M1' = M1 * M2
		bool        operator==(const Matrix& rhs) const;   // exact compare, no epsilon
		bool        operator!=(const Matrix& rhs) const;   // exact compare, no epsilon
		float       operator[](int index) const;            // subscript operator v[0], v[1]
		float& operator[](int index);                  // subscript operator v[0], v[1]

		// friends functions
		friend Matrix operator-(const Matrix& m);                     // unary operator (-)
		friend Matrix operator*(float scalar, const Matrix& m);       // pre-multiplication
		friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

		float getCofactor(float m0, float m1, float m2,
		float m3, float m4, float m5,
		float m6, float m7, float m8) const;

		float m[16];
	};

}

#endif // PLASMA_MATRIX_H



