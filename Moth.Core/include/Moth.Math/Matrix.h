#pragma once

#include "Math.h"


namespace Moth {
	namespace Math {
		namespace Matrix {
			template<class T>
			class Matrix {
			public:
				union {
					T m[16];
					T _m[4][4];
				};

			public:
				Matrix(T m00, T m01, T m02, T m03,
					   T m10, T m11, T m12, T m13,
					   T m20, T m21, T m22, T m23,
					   T m30, T m31, T m32, T m33) :
					m { m00, m01, m02, m03,
					    m10, m11, m12, m13,
					    m20, m21, m22, m23,
					    m30, m31, m32, m33 } { }
				Matrix(const Matrix& b) :
					m{ b._m[0][0], b._m[0][1], b._m[0][2], b._m[0][3],
					   b._m[1][0], b._m[1][1], b._m[1][2], b._m[1][3],
					   b._m[2][0], b._m[2][1], b._m[2][2], b._m[2][3],
					   b._m[3][0], b._m[3][1], b._m[3][2], b._m[3][3] }
				{ }

				inline static Matrix Zero() {
					return Matrix(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
								  static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
								  static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
								  static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
				}

				inline static Matrix Identity() {
					return Matrix(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
								  static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
								  static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
								  static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
				}

				inline Matrix Add(const Matrix& b) {
					return Matrix(this->_m[0][0] + b._m[0][0], this->_m[0][1] + b._m[0][1], this->_m[0][2] + b._m[0][2], this->_m[0][3] + b._m[0][3],
								  this->_m[1][0] + b._m[1][0], this->_m[1][1] + b._m[1][1], this->_m[1][2] + b._m[1][2], this->_m[1][3] + b._m[1][3],
								  this->_m[2][0] + b._m[2][0], this->_m[2][1] + b._m[2][1], this->_m[2][2] + b._m[2][2], this->_m[2][3] + b._m[2][3],
								  this->_m[3][0] + b._m[3][0], this->_m[3][1] + b._m[3][1], this->_m[3][2] + b._m[3][2], this->_m[3][3] + b._m[3][3]);
				}
				inline Matrix Add(T v) {
					return Matrix(this->_m[0][0] + v, this->_m[0][1] + v, this->_m[0][2] + v, this->_m[0][3] + v,
								  this->_m[1][0] + v, this->_m[1][1] + v, this->_m[1][2] + v, this->_m[1][3] + v,
								  this->_m[2][0] + v, this->_m[2][1] + v, this->_m[2][2] + v, this->_m[2][3] + v,
								  this->_m[3][0] + v, this->_m[3][1] + v, this->_m[3][2] + v, this->_m[3][3] + v);
				}
				inline Matrix Sub(const Matrix& b) {
					return Matrix(this->_m[0][0] - b._m[0][0], this->_m[0][1] - b._m[0][1], this->_m[0][2] - b._m[0][2], this->_m[0][3] - b._m[0][3],
								  this->_m[1][0] - b._m[1][0], this->_m[1][1] - b._m[1][1], this->_m[1][2] - b._m[1][2], this->_m[1][3] - b._m[1][3],
								  this->_m[2][0] - b._m[2][0], this->_m[2][1] - b._m[2][1], this->_m[2][2] - b._m[2][2], this->_m[2][3] - b._m[2][3],
								  this->_m[3][0] - b._m[3][0], this->_m[3][1] - b._m[3][1], this->_m[3][2] - b._m[3][2], this->_m[3][3] - b._m[3][3]);
				}
				inline Matrix Sub(T v) {
					return Matrix(this->_m[0][0] - v, this->_m[0][1] - v, this->_m[0][2] - v, this->_m[0][3] - v,
								  this->_m[1][0] - v, this->_m[1][1] - v, this->_m[1][2] - v, this->_m[1][3] - v,
								  this->_m[2][0] - v, this->_m[2][1] - v, this->_m[2][2] - v, this->_m[2][3] - v,
								  this->_m[3][0] - v, this->_m[3][1] - v, this->_m[3][2] - v, this->_m[3][3] - v);
				}
				inline Matrix Mul(const Matrix& b) {
					Matrix r;
					r._m[0][0] = Vector::Vector4<T>::Dot(this->_m[0][0], this->_m[0][1], this->_m[0][2], this->_m[0][3], b._m[0][0], b._m[1][0], b._m[2][0], b._m[3][0]);
					r._m[0][1] = Vector::Vector4<T>::Dot(this->_m[0][0], this->_m[0][1], this->_m[0][2], this->_m[0][3], b._m[0][1], b._m[1][1], b._m[2][1], b._m[3][1]);
					r._m[0][2] = Vector::Vector4<T>::Dot(this->_m[0][0], this->_m[0][1], this->_m[0][2], this->_m[0][3], b._m[0][2], b._m[1][2], b._m[2][2], b._m[3][2]);
					r._m[0][3] = Vector::Vector4<T>::Dot(this->_m[0][0], this->_m[0][1], this->_m[0][2], this->_m[0][3], b._m[0][3], b._m[1][3], b._m[2][3], b._m[3][3]);
					
					r._m[1][0] = Vector::Vector4<T>::Dot(this->_m[1][0], this->_m[1][1], this->_m[1][2], this->_m[1][3], b._m[0][0], b._m[1][0], b._m[2][0], b._m[3][0]);
					r._m[1][1] = Vector::Vector4<T>::Dot(this->_m[1][0], this->_m[1][1], this->_m[1][2], this->_m[1][3], b._m[0][1], b._m[1][1], b._m[2][1], b._m[3][1]);
					r._m[1][2] = Vector::Vector4<T>::Dot(this->_m[1][0], this->_m[1][1], this->_m[1][2], this->_m[1][3], b._m[0][2], b._m[1][2], b._m[2][2], b._m[3][2]);
					r._m[1][3] = Vector::Vector4<T>::Dot(this->_m[1][0], this->_m[1][1], this->_m[1][2], this->_m[1][3], b._m[0][3], b._m[1][3], b._m[2][3], b._m[3][3]);
					
					r._m[2][0] = Vector::Vector4<T>::Dot(this->_m[2][0], this->_m[2][1], this->_m[2][2], this->_m[2][3], b._m[0][0], b._m[1][0], b._m[2][0], b._m[3][0]);
					r._m[2][1] = Vector::Vector4<T>::Dot(this->_m[2][0], this->_m[2][1], this->_m[2][2], this->_m[2][3], b._m[0][1], b._m[1][1], b._m[2][1], b._m[3][1]);
					r._m[2][2] = Vector::Vector4<T>::Dot(this->_m[2][0], this->_m[2][1], this->_m[2][2], this->_m[2][3], b._m[0][2], b._m[1][2], b._m[2][2], b._m[3][2]);
					r._m[2][3] = Vector::Vector4<T>::Dot(this->_m[2][0], this->_m[2][1], this->_m[2][2], this->_m[2][3], b._m[0][3], b._m[1][3], b._m[2][3], b._m[3][3]);
					
					r._m[3][0] = Vector::Vector4<T>::Dot(this->_m[3][0], this->_m[3][1], this->_m[3][2], this->_m[3][3], b._m[0][0], b._m[1][0], b._m[2][0], b._m[3][0]);
					r._m[3][1] = Vector::Vector4<T>::Dot(this->_m[3][0], this->_m[3][1], this->_m[3][2], this->_m[3][3], b._m[0][1], b._m[1][1], b._m[2][1], b._m[3][1]);
					r._m[3][2] = Vector::Vector4<T>::Dot(this->_m[3][0], this->_m[3][1], this->_m[3][2], this->_m[3][3], b._m[0][2], b._m[1][2], b._m[2][2], b._m[3][2]);
					r._m[3][3] = Vector::Vector4<T>::Dot(this->_m[3][0], this->_m[3][1], this->_m[3][2], this->_m[3][3], b._m[0][3], b._m[1][3], b._m[2][3], b._m[3][3]);
					return r;
				}
				inline Matrix Mul(T v) {
					return Matrix(this->_m[0][0] * v, this->_m[0][1] * v, this->_m[0][2] * v, this->_m[0][3] * v,
								  this->_m[1][0] * v, this->_m[1][1] * v, this->_m[1][2] * v, this->_m[1][3] * v,
								  this->_m[2][0] * v, this->_m[2][1] * v, this->_m[2][2] * v, this->_m[2][3] * v,
								  this->_m[3][0] * v, this->_m[3][1] * v, this->_m[3][2] * v, this->_m[3][3] * v);
				}
				inline Matrix Div(const Matrix& b) { return this->Mul(Matrix::Inverse(b)); }
				inline Matrix Div(T v) {
					return Matrix(this->_m[0][0] / v, this->_m[0][1] / v, this->_m[0][2] / v, this->_m[0][3] / v,
								  this->_m[1][0] / v, this->_m[1][1] / v, this->_m[1][2] / v, this->_m[1][3] / v,
								  this->_m[2][0] / v, this->_m[2][1] / v, this->_m[2][2] / v, this->_m[2][3] / v,
								  this->_m[3][0] / v, this->_m[3][1] / v, this->_m[3][2] / v, this->_m[3][3] / v);
				}

				inline Matrix  operator+ (const Matrix& b) { return this->Add(b); }
				inline Matrix& operator+=(const Matrix& b) { *this = *this + b; return *this; }
				inline Matrix  operator+ (T v)			   { return this->Add(v); }
				inline Matrix& operator+=(T v)			   { *this = *this + v; return *this; }
				inline Matrix  operator- (const Matrix& b) { return this->Sub(b); }
				inline Matrix& operator-=(const Matrix& b) { *this = *this - b; return *this; }
				inline Matrix  operator- (T v)			   { return this->Sub(v); }
				inline Matrix& operator-=(T v)			   { *this = *this - v; return *this; }
				inline Matrix  operator* (const Matrix& b) { return this->Mul(b); }
				inline Matrix& operator*=(const Matrix& b) { *this = *this * b; return *this; }
				inline Matrix  operator* (T v)			   { return this->Mul(v); }
				inline Matrix& operator*=(T v)			   { *this = *this * v; return *this; }
				inline Matrix  operator/ (const Matrix& b) { return this->Div(b); }
				inline Matrix& operator/=(const Matrix& b) { *this = *this / b; return *this; }
				inline Matrix  operator/ (T v)			   { return this->Div(v); }
				inline Matrix& operator/=(T v)			   { *this = *this / v; return *this; }
				inline bool operator==(const Matrix& b) {
					return (this->_m[0][0] == b._m[0][0] && this->_m[0][1] == b._m[0][1] && this->_m[0][2] == b._m[0][2] && this->_m[0][3] == b._m[0][3] &&
							this->_m[1][0] == b._m[1][0] && this->_m[1][1] == b._m[1][1] && this->_m[1][2] == b._m[1][2] && this->_m[1][3] == b._m[1][3] &&
							this->_m[2][0] == b._m[2][0] && this->_m[2][1] == b._m[2][1] && this->_m[2][2] == b._m[2][2] && this->_m[2][3] == b._m[2][3] &&
							this->_m[3][0] == b._m[3][0] && this->_m[3][1] == b._m[3][1] && this->_m[3][2] == b._m[3][2] && this->_m[3][3] == b._m[3][3]);
				}
				inline bool operator!=(const Matrix& b) {
					return (this->_m[0][0] != b._m[0][0] || this->_m[0][1] != b._m[0][1] || this->_m[0][2] != b._m[0][2] || this->_m[0][3] != b._m[0][3] ||
							this->_m[1][0] != b._m[1][0] || this->_m[1][1] != b._m[1][1] || this->_m[1][2] != b._m[1][2] || this->_m[1][3] != b._m[1][3] ||
							this->_m[2][0] != b._m[2][0] || this->_m[2][1] != b._m[2][1] || this->_m[2][2] != b._m[2][2] || this->_m[2][3] != b._m[2][3] ||
							this->_m[3][0] != b._m[3][0] || this->_m[3][1] != b._m[3][1] || this->_m[3][2] != b._m[3][2] || this->_m[3][3] != b._m[3][3]);
				}

				inline T Determinant() {
					return _m[0][0] * Matrix::Minor(*this, 1, 2, 3, 1, 2, 3) -
						   _m[0][1] * Matrix::Minor(*this, 1, 2, 3, 0, 2, 3) +
						   _m[0][2] * Matrix::Minor(*this, 1, 2, 3, 0, 1, 3) -
						   _m[0][3] * Matrix::Minor(*this, 1, 2, 3, 0, 1, 2);
				}

				static Matrix Inverse(const Matrix& b) {
					T m00 = b._m[0][0], m01 = b._m[0][1], m02 = b._m[0][2], m03 = b._m[0][3],
					  m10 = b._m[1][0], m11 = b._m[1][1], m12 = b._m[1][2], m13 = b._m[1][3],
					  m20 = b._m[2][0], m21 = b._m[2][1], m22 = b._m[2][2], m23 = b._m[2][3],
					  m30 = b._m[3][0], m31 = b._m[3][1], m32 = b._m[3][2], m33 = b._m[3][3];

					T v0 = m20 * m31 - m21 * m30;
					T v1 = m20 * m32 - m22 * m30;
					T v2 = m20 * m33 - m23 * m30;
					T v3 = m21 * m32 - m22 * m31;
					T v4 = m21 * m33 - m23 * m31;
					T v5 = m22 * m33 - m23 * m32;

					T t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
					T t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
					T t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
					T t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

					T invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

					T d00 = t00 * invDet;
					T d10 = t10 * invDet;
					T d20 = t20 * invDet;
					T d30 = t30 * invDet;

					T d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
					T d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
					T d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
					T d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

					v0 = m10 * m31 - m11 * m30;
					v1 = m10 * m32 - m12 * m30;
					v2 = m10 * m33 - m13 * m30;
					v3 = m11 * m32 - m12 * m31;
					v4 = m11 * m33 - m13 * m31;
					v5 = m12 * m33 - m13 * m32;

					T d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
					T d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
					T d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
					T d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

					v0 = m21 * m10 - m20 * m11;
					v1 = m22 * m10 - m20 * m12;
					v2 = m23 * m10 - m20 * m13;
					v3 = m22 * m11 - m21 * m12;
					v4 = m23 * m11 - m21 * m13;
					v5 = m23 * m12 - m22 * m13;

					T d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
					T d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
					T d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
					T d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

					return Matrix(d00, d01, d02, d03,
								  d10, d11, d12, d13,
								  d20, d21, d22, d23,
								  d30, d31, d32, d33);
				}

				Matrix& Inverse() {
					Matrix r = Matrix::Inverse(*this);
					this->_m[0][0] = r._m[0][0], this->_m[0][1] = r._m[0][1], this->_m[0][2] = r._m[0][2], this->_m[0][3] = r._m[0][3],
					this->_m[1][0] = r._m[1][0], this->_m[1][1] = r._m[1][1], this->_m[1][2] = r._m[1][2], this->_m[1][3] = r._m[1][3],
					this->_m[2][0] = r._m[2][0], this->_m[2][1] = r._m[2][1], this->_m[2][2] = r._m[2][2], this->_m[2][3] = r._m[2][3],
					this->_m[3][0] = r._m[3][0], this->_m[3][1] = r._m[3][1], this->_m[3][2] = r._m[3][2], this->_m[3][3] = r._m[3][3];
					return *this;
				}


				~Matrix() { };

			private:
				Matrix() { };

				inline static T Minor(const Matrix& m, size_t r0, size_t r1, size_t r2, size_t c0, size_t c1, size_t c2) {
					return m._m[r0][c0] * (m._m[r1][c1] * m._m[r2][c2] - m._m[r2][c1] * m._m[r1][c2]) -
						   m._m[r0][c1] * (m._m[r1][c0] * m._m[r2][c2] - m._m[r2][c0] * m._m[r1][c2]) +
						   m._m[r0][c2] * (m._m[r1][c0] * m._m[r2][c1] - m._m[r2][c0] * m._m[r1][c1]);
				}
			};
		}

		typedef Matrix::Matrix<Moth_Float32> FMatrix;
		typedef Matrix::Matrix<Moth_Float64> DMatrix;
	}
}