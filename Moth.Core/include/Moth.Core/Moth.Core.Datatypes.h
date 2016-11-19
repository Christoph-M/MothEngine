#pragma once
#include <inttypes.h>
#include <assert.h>

// *************************** Character ***************************
typedef char	 Moth_Char8;
typedef wchar_t  Moth_Char16;
typedef char*	 Moth_CString;
typedef wchar_t* Moth_WString;

#ifdef MOTH_CHAR_8
	typedef Moth_Char8 Moth_Char;
	typedef Moth_CString Moth_String;
#else
	typedef Moth_Char16 Moth_Char;
	typedef Moth_WString Moth_String;
#endif

// *************************** Integer ***************************
typedef int8_t  Moth_Int8;
typedef int16_t Moth_Int16;
typedef int32_t Moth_Int32;
typedef int64_t Moth_Int64;

#ifdef MOTH_INT_8
	typedef Moth_Int8  Moth_Int;
#elif MOTH_INT_16
	typedef Moth_Int16 Moth_Int;
#elif MOTH_INT_64
	typedef Moth_Int64 Moth_Int;
#else
	typedef Moth_Int32 Moth_Int;
#endif

// *************************** Unsigned Integer ***************************
typedef uint8_t  Moth_UInt8;
typedef uint16_t Moth_UInt16;
typedef uint32_t Moth_UInt32;
typedef uint64_t Moth_UInt64;

#ifdef MOTH_UINT_8
	typedef Moth_UInt8  Moth_UInt;
#elif MOTH_UINT_16
	typedef Moth_UInt16 Moth_UInt;
#elif MOTH_UINT_64
	typedef Moth_UInt64 Moth_UInt;
#else
	typedef Moth_UInt32 Moth_UInt;
#endif

// *************************** Floating Point ***************************
typedef float Moth_Float32;
typedef double Moth_Float64;

#ifdef MOTH_FLOAT_64
	typedef Moth_Float64 Moth_Float;
#else
	typedef Moth_Float32 Moth_Float;
#endif




//#define CHECK_TYPE(condition, size) (sizeof(condition) == size)
//
//void test()
//{
//	assert(CHECK_TYPE(float, 4));
//	assert(CHECK_TYPE(double, 8));
//}