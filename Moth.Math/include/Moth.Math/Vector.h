#pragma once

#include <cmath>

#include "Moth.Core\Moth.Core.Datatypes.h"


namespace Moth {
	namespace Math {
		namespace Vector {
			template<class T>
			struct Vector {
				union {
					struct { T x, y, z; } v;
					T a[3];
				};

				inline Vector Add(const Vector& b) { return Vector { this->v.x + b.v.x, this->v.y + b.v.y, this->v.z + b.v.z }; }
				inline Vector Add(const T v)	   { return Vector { this->v.x + v,     this->v.y + v,     this->v.z + v	 }; }
				inline Vector Sub(const Vector& b) { return Vector { this->v.x - b.v.x, this->v.y - b.v.y, this->v.z - b.v.z }; }
				inline Vector Sub(const T v)	   { return Vector { this->v.x - v,     this->v.y - v,     this->v.z - v	 }; }
				inline Vector Mul(const Vector& b) { return Vector { this->v.x * b.v.x, this->v.y * b.v.y, this->v.z * b.v.z }; }
				inline Vector Mul(const T v)	   { return Vector { this->v.x * v,     this->v.y * v,     this->v.z * v	 }; }
				inline Vector Div(const Vector& b) { return Vector { this->v.x / b.v.x, this->v.y / b.v.y, this->v.z / b.v.z }; }
				inline Vector Div(const T v)	   { return Vector { this->v.x / v,	    this->v.y / v,     this->v.z / v	 }; }

				inline Vector operator+(const Vector& b)  { return this->Add(b); }
				inline void   operator+=(const Vector& b) { *this = *this + b;   }
				inline Vector operator+(const T v)		  { return this->Add(v); }
				inline void   operator+=(const T v)		  { *this = *this + v;   }
				inline Vector operator-(const Vector& b)  { return this->Sub(b); }
				inline void   operator-=(const Vector& b) { *this = *this - b;   }
				inline Vector operator-(const T v)		  { return this->Sub(v); }
				inline void   operator-=(const T v)		  { *this = *this - v;   }
				inline Vector operator*(const Vector& b)  { return this->Mul(b); }
				inline void   operator*=(const Vector& b) { *this = *this * b;   }
				inline Vector operator*(const T v)		  { return this->Mul(v); }
				inline void   operator*=(const T v)		  { *this = *this * v;   }
				inline Vector operator/(const Vector& b)  { return this->Div(b); }
				inline void   operator/=(const Vector& b) { *this = *this / b;   }
				inline Vector operator/(const T v)		  { return this->Div(v); }
				inline void   operator/=(const T v)		  { *this = *this / v;	 }
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

				inline T Length() { return sqrt(this->v.x * this->v.x + this->v.y * this->v.y + this->v.z * this->v.z); }
				inline Vector Normalize() {
					*this /= this->Length();
					return *this;
				}
			};

			template<class T>
			struct Vector2 {
				union {
					struct { T x, y; } v;
					T a[2];
				};

				inline Vector2 Add(const Vector2& b) { return Vector2 { this->v.x + b.v.x, this->v.y + b.v.y }; }
				inline Vector2 Add(const T v)		 { return Vector2 { this->v.x + v,     this->v.y + v	 }; }
				inline Vector2 Sub(const Vector2& b) { return Vector2 { this->v.x - b.v.x, this->v.y - b.v.y }; }
				inline Vector2 Sub(const T v)	     { return Vector2 { this->v.x - v,     this->v.y - v	 }; }
				inline Vector2 Mul(const Vector2& b) { return Vector2 { this->v.x * b.v.x, this->v.y * b.v.y }; }
				inline Vector2 Mul(const T v)	     { return Vector2 { this->v.x * v,     this->v.y * v	 }; }
				inline Vector2 Div(const Vector2& b) { return Vector2 { this->v.x / b.v.x, this->v.y / b.v.y }; }
				inline Vector2 Div(const T v)	     { return Vector2 { this->v.x / v,	   this->v.y / v	 }; }

				inline Vector2 operator+(const Vector2& b)  { return this->Add(b); }
				inline void    operator+=(const Vector2& b) { *this = *this + b;   }
				inline Vector2 operator+(const T v)		    { return this->Add(v); }
				inline void    operator+=(const T v)	    { *this = *this + v;   }
				inline Vector2 operator-(const Vector2& b)  { return this->Sub(b); }
				inline void    operator-=(const Vector2& b) { *this = *this - b;   }
				inline Vector2 operator-(const T v)		    { return this->Sub(v); }
				inline void    operator-=(const T v)	    { *this = *this - v;   }
				inline Vector2 operator*(const Vector2& b)  { return this->Mul(b); }
				inline void    operator*=(const Vector2& b) { *this = *this * b;   }
				inline Vector2 operator*(const T v)		    { return this->Mul(v); }
				inline void    operator*=(const T v)	    { *this = *this * v;   }
				inline Vector2 operator/(const Vector2& b)  { return this->Div(b); }
				inline void    operator/=(const Vector2& b) { *this = *this / b;   }
				inline Vector2 operator/(const T v)		    { return this->Div(v); }
				inline void    operator/=(const T v)	    { *this = *this / v;   }
				inline bool operator==(const Vector2& b) { return (this->v.x == b.v.x) && (this->v.y == b.v.y); }
				inline bool operator!=(const Vector2& b) { return (this->v.x != b.v.x) || (this->v.y != b.v.y); }

				inline T Dot(const Vector2& b) { return (this->v.x * b.v.x + this->v.y * b.v.y); }

				inline T Length() { return sqrt(this->v.x * this->v.x + this->v.y * this->v.y); }
				inline Vector2 Normalize() {
					*this /= this->Length();
					return *this;
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