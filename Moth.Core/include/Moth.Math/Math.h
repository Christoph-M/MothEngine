#pragma once

#include <cmath>

#include "..\Moth.Core\Moth.Core.Datatypes.h"


namespace Moth {
	namespace Math {
	#define PI  3.14159265359f
	#define TAU 6.28318530718f


		template<class T>
		struct Math {
			inline static T Clamp(T value) { return Math<T>::Clamp(value, static_cast<T>(0), static_cast<T>(1)); }
			inline static T Clamp(T value, T minValue, T maxValue) { return max(minValue, min(maxValue, value)); }
		};

		typedef Math<Moth_Float32> FMath;
		typedef Math<Moth_Float64> DMath;
		typedef Math<Moth_Int32>   IMath;
	}
}