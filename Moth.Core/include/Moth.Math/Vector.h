#pragma once

#include "Math.h"


namespace Moth {
	namespace Math {
		namespace Vector {
			template<class T>
			struct Vector2;
			template<class T>
			struct Vector4;

			template<class T>
			struct Vector {
				union {
					struct { T x, y, z; } v;
					T a[3];
				};
				
				inline static Vector Zero()	   { return Vector { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 0) }; }
				inline static Vector One()	   { return Vector { static_cast<T>( 1), static_cast<T>( 1), static_cast<T>( 1) }; }
				inline static Vector Up()	   { return Vector { static_cast<T>( 0), static_cast<T>( 1), static_cast<T>( 0) }; }
				inline static Vector Down()	   { return Vector { static_cast<T>( 0), static_cast<T>(-1), static_cast<T>( 0) }; }
				inline static Vector Right()   { return Vector { static_cast<T>( 1), static_cast<T>( 0), static_cast<T>( 0) }; }
				inline static Vector Left()	   { return Vector { static_cast<T>(-1), static_cast<T>( 0), static_cast<T>( 0) }; }
				inline static Vector Forward() { return Vector { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 1) }; }
				inline static Vector Back()	   { return Vector { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>(-1) }; }

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

				inline T operator[](size_t pos) { return this->a[pos]; }

				inline T Dot(const Vector& b) { return (this->v.x * b.v.x + this->v.y * b.v.y + this->v.z * b.v.z); }
				inline T Dot(const Vector2<T>& b) { return (this->v.x * b.v.x + this->v.y * b.v.y); }
				inline static T Dot(const Vector& a, const Vector& b)	  { return (a.v.x * b.v.x + a.v.y * b.v.y + a.v.z * b.v.z); }
				inline static T Dot(const Vector& a, const Vector2<T>& b) { return (a.v.x * b.v.x + a.v.y * b.v.y); }
				inline static T Dot(T ax, T ay, T az, T bx, T by, T bz) { return (ax * bx + ay * by + az * bz); }
				inline Vector Cross(const Vector& b) {
					return Vector {
						this->v.y * b.v.z - this->v.z * b.v.y,
						this->v.z * b.v.x - this->v.x * b.v.z,
						this->v.x * b.v.y - this->v.y * b.v.x
					};
				}
				inline Vector Cross(const Vector2<T>& b) { return Vector{ -(this->v.z * b.v.y), this->v.z * b.v.x, this->v.x * b.v.y - this->v.y * b.v.x }; }

				inline T Distance(const Vector& b) { return (*this - b).Length(); }
				inline T Length() { return sqrt(this->v.x * this->v.x + this->v.y * this->v.y + this->v.z * this->v.z); }
				inline Vector Normalize() { *this /= this->Length(); return *this; }

				inline static Vector Lerp(const Vector& start, const Vector& end, T time) { return (start + (end - start) * time); }
				inline static Vector NLerp(const Vector& start, const Vector& end, T time) { return Vector::Lerp(start, end, time).Normalize(); }
				static Vector SLerp(const Vector& start, const Vector& end, T time) {
					T dot = start.Dot(end);
					Math<T>::Clamp(dot, static_cast<T>(-1), static_cast<T>(1));
					T theta = acos(dot) * time;
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

				inline static Vector2 Zero()  { return Vector2 { static_cast<T>( 0), static_cast<T>( 0) }; }
				inline static Vector2 One()	  { return Vector2 { static_cast<T>( 1), static_cast<T>( 1) }; }
				inline static Vector2 Up()	  { return Vector2 { static_cast<T>( 0), static_cast<T>( 1) }; }
				inline static Vector2 Down()  { return Vector2 { static_cast<T>( 0), static_cast<T>(-1) }; }
				inline static Vector2 Right() { return Vector2 { static_cast<T>( 1), static_cast<T>( 0) }; }
				inline static Vector2 Left()  { return Vector2 { static_cast<T>(-1), static_cast<T>( 0) }; }

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

				inline T operator[](size_t pos) { return this->a[pos]; }

				inline T Dot(const Vector2& b) { return (this->v.x * b.v.x + this->v.y * b.v.y); }
				inline static T Dot(const Vector2& a, const Vector2& b) { return (a.v.x * b.v.x + a.v.y * b.v.y); }
				inline static T Dot(T ax, T ay, T bx, T by) { return (ax * bx + ay * by); }
				
				inline T Distance(const Vector2& b) { return (*this - b).Length(); }
				inline T Length() { return sqrt(this->v.x * this->v.x + this->v.y * this->v.y); }
				inline Vector2 Normalize() {
					*this /= this->Length();
					return *this;
				}

				inline static Vector2 Lerp(const Vector2& start, const Vector2& end, T time) { return (start + (end - start) * time); }
				inline static Vector2 NLerp(const Vector2& start, const Vector2& end, T time) { return Vector2::Lerp(start, end, time).Normalize(); }
				static Vector2 SLerp(const Vector2& start, const Vector2& end, T time) {
					T dot = start.Dot(end);
					Math<T>::Clamp(dot, static_cast<T>(-1), static_cast<T>(1));
					T theta = acos(dot) * time;
					Vector2 relativeVec = end - start * dot;
					relativeVec.Normalize();
					return ((start * cos(theta) + (relativeVec * sin(theta))));
				}
			};
			
			template<class T>
			struct Vector4 {
				union {
					struct { T x, y, z, w; } v;
					T a[4];
				};
				
				inline static Vector4 Zero()	  { return Vector4 { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 0) }; }
				inline static Vector4 One()		  { return Vector4 { static_cast<T>( 1), static_cast<T>( 1), static_cast<T>( 1), static_cast<T>( 1) }; }
				inline static Vector4 Up()		  { return Vector4 { static_cast<T>( 0), static_cast<T>( 1), static_cast<T>( 0), static_cast<T>( 1) }; }
				inline static Vector4 Down()	  { return Vector4 { static_cast<T>( 0), static_cast<T>(-1), static_cast<T>( 0), static_cast<T>( 1) }; }
				inline static Vector4 Right()	  { return Vector4 { static_cast<T>( 1), static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 1) }; }
				inline static Vector4 Left()	  { return Vector4 { static_cast<T>(-1), static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 1) }; }
				inline static Vector4 Forward()   { return Vector4 { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 1), static_cast<T>( 1) }; }
				inline static Vector4 Back()	  { return Vector4 { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>(-1), static_cast<T>( 1) }; }
				inline static Vector4 PositiveW() { return Vector4 { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 1) }; }
				inline static Vector4 NegativeW() { return Vector4 { static_cast<T>( 0), static_cast<T>( 0), static_cast<T>( 0), static_cast<T>(-1) }; }

				inline Vector4 Add(const Vector4& b) { return Vector4 { this->v.x + b.v.x, this->v.y + b.v.y, this->v.z + b.v.z, this->v.w + b.v.w }; }
				inline Vector4 Add(const T v)		 { return Vector4 { this->v.x + v,     this->v.y + v,     this->v.z + v,	 this->v.w + v	   }; }
				inline Vector4 Sub(const Vector4& b) { return Vector4 { this->v.x - b.v.x, this->v.y - b.v.y, this->v.z - b.v.z, this->v.w - b.v.w }; }
				inline Vector4 Sub(const T v)		 { return Vector4 { this->v.x - v,     this->v.y - v,     this->v.z - v,	 this->v.w - v	   }; }
				inline Vector4 Mul(const Vector4& b) { return Vector4 { this->v.x * b.v.x, this->v.y * b.v.y, this->v.z * b.v.z, this->v.w * b.v.w }; }
				inline Vector4 Mul(const T v)		 { return Vector4 { this->v.x * v,     this->v.y * v,     this->v.z * v,	 this->v.w * v	   }; }
				inline Vector4 Div(const Vector4& b) { return Vector4 { this->v.x / b.v.x, this->v.y / b.v.y, this->v.z / b.v.z, this->v.w / b.v.w }; }
				inline Vector4 Div(const T v)		 { return Vector4 { this->v.x / v,	   this->v.y / v,     this->v.z / v,	 this->v.w / v	   }; }

				inline Vector4  operator+(const Vector4& b)  { return this->Add(b); }
				inline Vector4& operator+=(const Vector4& b) { *this = *this + b; return *this; }
				inline Vector4  operator+(const T v)		 { return this->Add(v); }
				inline Vector4& operator+=(const T v)		 { *this = *this + v; return *this; }
				inline Vector4  operator-(const Vector4& b)  { return this->Sub(b); }
				inline Vector4& operator-=(const Vector4& b) { *this = *this - b; return *this; }
				inline Vector4  operator-(const T v)		 { return this->Sub(v); }
				inline Vector4& operator-=(const T v)		 { *this = *this - v; return *this; }
				inline Vector4  operator*(const Vector4& b)  { return this->Mul(b); }
				inline Vector4& operator*=(const Vector4& b) { *this = *this * b; return *this; }
				inline Vector4  operator*(const T v)		 { return this->Mul(v); }
				inline Vector4& operator*=(const T v)		 { *this = *this * v; return *this; }
				inline Vector4  operator/(const Vector4& b)  { return this->Div(b); }
				inline Vector4& operator/=(const Vector4& b) { *this = *this / b; return *this; }
				inline Vector4  operator/(const T v)		 { return this->Div(v); }
				inline Vector4& operator/=(const T v)		 { *this = *this / v; return *this; }
				inline bool operator==(const Vector4& b) { return (this->v.x == b.v.x) && (this->v.y == b.v.y) && (this->v.z == b.v.z) && (this->v.w == b.v.w); }
				inline bool operator!=(const Vector4& b) { return (this->v.x != b.v.x) || (this->v.y != b.v.y) || (this->v.z != b.v.z) || (this->v.w != b.v.w); }

				inline T operator[](size_t pos) { return this->a[pos]; }

				inline T Dot(const Vector4& b) { return (this->v.x * b.v.x + this->v.y * b.v.y + this->v.z * b.v.z + this->v.w * b.v.w); }
				inline static T Dot(const Vector4& a, const Vector4& b) { return (a.v.x * b.v.x + a.v.y * b.v.y + a.v.z * b.v.z + a.v.w * b.v.w); }
				inline static T Dot(T ax, T ay, T az, T aw, T bx, T by, T bz, T bw) { return (ax * bx + ay * by + az * bz + aw * bw); }
				inline Vector<T> Cross3r3(const Vector<T>& b) {
					return Vector4 {
						this->v.y * b.v.z - this->v.z * b.v.y,
						this->v.z * b.v.x - this->v.x * b.v.z,
						this->v.x * b.v.y - this->v.y * b.v.x
					};
				}
				inline Vector<T> Cross3r3(const Vector4& b) { return this->Cross3r3(Vector<T> { b.v.x, b.v.y, b.v.z }); }
				inline Vector4 Cross3r4(const Vector<T>& b)	{ return Vector4 { this->Cross3r3(b), static_cast<T>(1) }; }
				inline Vector4 Cross3r4(const Vector4& b)	{ return Vector4 { this->Cross3r3(b), static_cast<T>(1) }; }

				inline T Distance(const Vector4& b) { return (*this - b).Length(); }
				inline T Length() { return sqrt(this->v.x * this->v.x + this->v.y * this->v.y + this->v.z * this->v.z + this->v.w * this->v.w); }
				inline Vector4 Normalize() {
					*this /= this->Length();
					return *this;
				}

				inline static Vector4 Lerp(const Vector4& start, const Vector4& end, T time) { return (start + (end - start) * time); }
				inline static Vector4 NLerp(const Vector4& start, const Vector4& end, T time) { return Vector4::Lerp(start, end, time).Normalize(); }
				static Vector4 SLerp(const Vector4& start, const Vector4& end, T time) {
					T dot = start.Dot(end);
					Math<T>::Clamp(dot, static_cast<T>(-1), static_cast<T>(1));
					T theta = acos(dot) * time;
					Vector4 relativeVec = end - start * dot;
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
		
		typedef Vector::Vector4<Moth_Float32> FVector4;
		typedef Vector::Vector4<Moth_Float64> DVector4;
		typedef Vector::Vector4<Moth_Int8>    CVector4;
		typedef Vector::Vector4<Moth_Int16>   SVector4;
		typedef Vector::Vector4<Moth_Int32>   IVector4;
		typedef Vector::Vector4<Moth_Int64>   LVector4;
	}
}