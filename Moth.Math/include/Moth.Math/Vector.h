#pragma once

#include "Math.h"


namespace Moth {
	namespace Math {
		namespace Vector {
			template<class T>
			struct Vector {
				union {
					struct { T x, y, z; } v;
					T a[3];
				};
				
				inline Vector Zero()	{ return Vector { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 0) } }
				inline Vector One()		{ return Vector { static_cast<T>( 1), static_cast<T>( 1), static_cast<T>( 1) } }
				inline Vector Up()		{ return Vector { static_cast<T>( 0), static_cast<T>( 1), static_cast<T>( 0) } }
				inline Vector Down()	{ return Vector { static_cast<T>( 0), static_cast<T>(-1), static_cast<T>( 0) } }
				inline Vector Right()	{ return Vector { static_cast<T>( 1), static_cast<T>( 0), static_cast<T>( 0) } }
				inline Vector Left()	{ return Vector { static_cast<T>(-1), static_cast<T>( 0), static_cast<T>( 0) } }
				inline Vector Forward() { return Vector { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 1) } }
				inline Vector Back()	{ return Vector { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>(-1) } }

				inline Vector Add(const Vector& b) { return Vector { this->v.x + b.v.x, this->v.y + b.v.y, this->v.z + b.v.z }; }
				inline Vector Add(const T v)	   { return Vector { this->v.x + v,     this->v.y + v,     this->v.z + v	 }; }
				inline Vector Sub(const Vector& b) { return Vector { this->v.x - b.v.x, this->v.y - b.v.y, this->v.z - b.v.z }; }
				inline Vector Sub(const T v)	   { return Vector { this->v.x - v,     this->v.y - v,     this->v.z - v	 }; }
				inline Vector Mul(const Vector& b) { return Vector { this->v.x * b.v.x, this->v.y * b.v.y, this->v.z * b.v.z }; }
				inline Vector Mul(const T v)	   { return Vector { this->v.x * v,     this->v.y * v,     this->v.z * v	 }; }
				inline Vector Div(const Vector& b) { return Vector { this->v.x / b.v.x, this->v.y / b.v.y, this->v.z / b.v.z }; }
				inline Vector Div(const T v)	   { return Vector { this->v.x / v,	    this->v.y / v,     this->v.z / v	 }; }

				inline Vector  operator+(const Vector& b)  { return this->Add(b); }
				inline Vector& operator+=(const Vector& b) { *this = *this + b; return *this; }
				inline Vector  operator+(const T v)		   { return this->Add(v); }
				inline Vector& operator+=(const T v)	   { *this = *this + v; return *this; }
				inline Vector  operator-(const Vector& b)  { return this->Sub(b); }
				inline Vector& operator-=(const Vector& b) { *this = *this - b; return *this; }
				inline Vector  operator-(const T v)		   { return this->Sub(v); }
				inline Vector& operator-=(const T v)	   { *this = *this - v; return *this; }
				inline Vector  operator*(const Vector& b)  { return this->Mul(b); }
				inline Vector& operator*=(const Vector& b) { *this = *this * b; return *this; }
				inline Vector  operator*(const T v)		   { return this->Mul(v); }
				inline Vector& operator*=(const T v)	   { *this = *this * v; return *this; }
				inline Vector  operator/(const Vector& b)  { return this->Div(b); }
				inline Vector& operator/=(const Vector& b) { *this = *this / b; return *this; }
				inline Vector  operator/(const T v)		   { return this->Div(v); }
				inline Vector& operator/=(const T v)	   { *this = *this / v; return *this; }
				inline bool operator==(const Vector& b) { return (this->v.x == b.v.x) && (this->v.y == b.v.y) && (this->v.z == b.v.z); }
				inline bool operator!=(const Vector& b) { return (this->v.x != b.v.x) || (this->v.y != b.v.y) || (this->v.z != b.v.z); }

				inline T Dot(const Vector& b) { return (this->v.x * b.v.x + this->v.y * b.v.y + this->v.z * b.v.z); }
				inline Vector Cross(const Vector& b) {
					return Vector {
						this->v.y * b.v.z - this->v.z * b.v.y,
						this->v.z * b.v.x - this->v.x * b.v.z,
						this->v.x * b.v.y - this->v.y * b.v.x
					};
				}

				inline T Distance(const Vector& b) { return (*this - b).Length(); }
				inline T Length() { return sqrt(this->v.x * this->v.x + this->v.y * this->v.y + this->v.z * this->v.z); }
				inline Vector Normalize() {
					*this /= this->Length();
					return *this;
				}

				inline static Vector Lerp(const Vector& start, const Vector& end, T time) { return (start + (end - start) * time); }
				inline static Vector NLerp(const Vector& start, const Vector& end, T time) { return Vector::Lerp(start, end, time).Normalize(); }
				static Vector SLerp(const Vector& start, const Vector& end, T time) {
					T dot = start.Dot(end);
					Math<T>::Clamp(dot, static_cast<T>(-1), static_cast<T>(1));
					T theta = acos(dot);
					Vector relativeVec = end - start * dot;
					relativeVec.Normalize();
					return ((start * cos(theta) + (relativeVec * sin(theta))));
				}
			};

			template<class T>
			struct Vector2 {
				union {
					struct { T x, y; } v;
					T a[2];
				};

				inline Vector2 Zero()	{ return Vector2 { static_cast<T>( 0), static_cast<T>( 0) } }
				inline Vector2 One()	{ return Vector2 { static_cast<T>( 1), static_cast<T>( 1) } }
				inline Vector2 Up()		{ return Vector2 { static_cast<T>( 0), static_cast<T>( 1) } }
				inline Vector2 Down()	{ return Vector2 { static_cast<T>( 0), static_cast<T>(-1) } }
				inline Vector2 Right()	{ return Vector2 { static_cast<T>( 1), static_cast<T>( 0) } }
				inline Vector2 Left()	{ return Vector2 { static_cast<T>(-1), static_cast<T>( 0) } }

				inline Vector2 Add(const Vector2& b) { return Vector2 { this->v.x + b.v.x, this->v.y + b.v.y }; }
				inline Vector2 Add(const T v)		 { return Vector2 { this->v.x + v,     this->v.y + v	 }; }
				inline Vector2 Sub(const Vector2& b) { return Vector2 { this->v.x - b.v.x, this->v.y - b.v.y }; }
				inline Vector2 Sub(const T v)	     { return Vector2 { this->v.x - v,     this->v.y - v	 }; }
				inline Vector2 Mul(const Vector2& b) { return Vector2 { this->v.x * b.v.x, this->v.y * b.v.y }; }
				inline Vector2 Mul(const T v)	     { return Vector2 { this->v.x * v,     this->v.y * v	 }; }
				inline Vector2 Div(const Vector2& b) { return Vector2 { this->v.x / b.v.x, this->v.y / b.v.y }; }
				inline Vector2 Div(const T v)	     { return Vector2 { this->v.x / v,	   this->v.y / v	 }; }

				inline Vector2  operator+(const Vector2& b)  { return this->Add(b); }
				inline Vector2& operator+=(const Vector2& b) { *this = *this + b; return *this; }
				inline Vector2  operator+(const T v)		 { return this->Add(v); }
				inline Vector2& operator+=(const T v)	     { *this = *this + v; return *this; }
				inline Vector2  operator-(const Vector2& b)  { return this->Sub(b); }
				inline Vector2& operator-=(const Vector2& b) { *this = *this - b; return *this; }
				inline Vector2  operator-(const T v)		 { return this->Sub(v); }
				inline Vector2& operator-=(const T v)	     { *this = *this - v; return *this; }
				inline Vector2  operator*(const Vector2& b)  { return this->Mul(b); }
				inline Vector2& operator*=(const Vector2& b) { *this = *this * b; return *this; }
				inline Vector2  operator*(const T v)		 { return this->Mul(v); }
				inline Vector2& operator*=(const T v)	     { *this = *this * v; return *this; }
				inline Vector2  operator/(const Vector2& b)  { return this->Div(b); }
				inline Vector2& operator/=(const Vector2& b) { *this = *this / b; return *this; }
				inline Vector2  operator/(const T v)		 { return this->Div(v); }
				inline Vector2& operator/=(const T v)	     { *this = *this / v; return *this; }
				inline bool operator==(const Vector2& b) { return (this->v.x == b.v.x) && (this->v.y == b.v.y); }
				inline bool operator!=(const Vector2& b) { return (this->v.x != b.v.x) || (this->v.y != b.v.y); }

				inline T Dot(const Vector2& b) { return (this->v.x * b.v.x + this->v.y * b.v.y); }
				
				inline T Distance(const Vector2& b) { return (*this - b).Length(); }
				inline T Length() { return sqrt(this->v.x * this->v.x + this->v.y * this->v.y); }
				inline Vector2 Normalize() {
					*this /= this->Length();
					return *this;
				}

				inline static Vector2 Lerp(const Vector2& start, const Vector2& end, T time) { return (start + (end - start) * time); }
				inline static Vector2 NLerp(const Vector2& start, const Vector2& end, T time) { return Vector::Lerp(start, end, time).Normalize(); }
				static Vector2 SLerp(const Vector2& start, const Vector2& end, T time) {
					T dot = start.Dot(end);
					Math<T>::Clamp(dot, static_cast<T>(-1), static_cast<T>(1));
					T theta = acos(dot);
					Vector2 relativeVec = end - start * dot;
					relativeVec.Normalize();
					return ((start * cos(theta) + (relativeVec * sin(theta))));
				}
			};
		}

		typedef Vector::Vector<Moth_Float32>  FVector;
		typedef Vector::Vector<Moth_Float64>  DVector;
		typedef Vector::Vector<Moth_Int8>     CVector;
		typedef Vector::Vector<Moth_Int16>    SVector;
		typedef Vector::Vector<Moth_Int32>    IVector;
		typedef Vector::Vector<Moth_Int64>    LVector;
		
		typedef Vector::Vector2<Moth_Float32> FVector2;
		typedef Vector::Vector2<Moth_Float64> DVector2;
		typedef Vector::Vector2<Moth_Int8>    CVector2;
		typedef Vector::Vector2<Moth_Int16>   SVector2;
		typedef Vector::Vector2<Moth_Int32>   IVector2;
		typedef Vector::Vector2<Moth_Int64>   LVector2;
	}
}