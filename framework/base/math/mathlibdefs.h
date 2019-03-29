///////////////////////////////////////////////////////////////////////////////////////
//  mathlibdefs.h
//
//  Inside library defines compilation functions specification
//  
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _MATH_LIB_DEFINES_H_
#define _MATH_LIB_DEFINES_H_

#define M_API

// In-line Function And Force In line Macros
#define M_INLINE       __inline
#ifdef __linux__
#define M_FORCEINL     __attribute__((always_inline)) inline
#elif _WIN32
#define M_FORCEINL     __forceinline
#else
#define M_FORCEINL     __inline
#endif // Force Inline For Different Platforms

// Primary Function That Has SSE Implementation
#if defined (MATH_SIMD_EXT)
#define MATH_PRIM_SSE
#endif //MATH_SIMD_EXT

// Library Uses ILM Functions In Converting Float Types Into Half Type
//#define MATH_ILM_HALF_CONVERSION

// Header that contains common macros needed to compile library and use externally
#include "mathdefscommon.h"


///////////////////////////////////////////////////////////////////////////////////////
// Square root computation precision preprocessor
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// Float square root computation defines
///////////////////////////////////////////////////////////////////////////////////////
// High precision float square root computation
#if defined (MATH_HIGH_PREC_FLOAT_SQRT)
//--#pragma message "High precision float square root calculation in algebra classes"

#define CMATH_VEC2_HIGH_PREC_FLOAT_SQRT
#define CMATH_VEC3_HIGH_PREC_FLOAT_SQRT
#define CMATH_VEC4_HIGH_PREC_FLOAT_SQRT
#define CMATH_PLANE_HIGH_PREC_FLOAT_SQRT
#define CMATH_MTX33_HIGH_PREC_FLOAT_SQRT
#define CMATH_MTX44_HIGH_PREC_FLOAT_SQRT
#define CMATH_QUAT_HIGH_PREC_FLOAT_SQRT

// Float table square root computation
#elif defined (MATH_FLOAT_TABLE_SQRT)
//--#pragma message "Table float square root calculation in algebra classes"

#define CMATH_VEC2_FLOAT_TABLE_SQRT
#define CMATH_VEC3_FLOAT_TABLE_SQRT
#define CMATH_VEC4_FLOAT_TABLE_SQRT
#define CMATH_MTX33_FLOAT_TABLE_SQRT
#define CMATH_MTX44_FLOAT_TABLE_SQRT
#define CMATH_QUAT_FLOAT_TABLE_SQRT
#define CMATH_PLANE_FLOAT_TABLE_SQRT

// Fast approximation float square root computation
#elif defined (MATH_FAST_FLOAT_SQRT)
//--#pragma message "Approximation float square root calculation in algebra classes"

#define CMATH_VEC2_FAST_FLOAT_SQRT
#define CMATH_VEC3_FAST_FLOAT_SQRT
#define CMATH_VEC4_FAST_FLOAT_SQRT
#define CMATH_MTX33_FAST_FLOAT_SQRT
#define CMATH_MTX44_FAST_FLOAT_SQRT
#define CMATH_QUAT_FAST_FLOAT_SQRT
#define CMATH_PLANE_FAST_FLOAT_SQRT

// Default float square root computation
//--#else
//--#pragma message "Default float square root calculation in algebra classes"
#endif // Square root computation precision preprocessor

///////////////////////////////////////////////////////////////////////////////////////
// Fixed square root computation defines
///////////////////////////////////////////////////////////////////////////////////////
// High precision float square root computation for fixed types
// Table float square root computation for fixed types
// Fast float square root computation for fixed types
// Fast int square root computation fot fixed types


///////////////////////////////////////////////////////////////////////////////////////
// Trigonometry computation precision preprocessor
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
// Float trigonometry computation defines
///////////////////////////////////////////////////////////////////////////////////////
// High precision float trigonometry computation
#if defined (MATH_HIGH_PREC_FLOAT_TRIGONOMETRY)
//--#pragma message "High precision float trigonometry calculation in algebra classes"

#define CMATH_VEC2_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_VEC3_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_VEC4_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_MTX33_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_MTX44_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_PLANE_HIGH_PREC_FLOAT_TRIGONOMETRY

// Float table trigonometry computation
#elif defined (MATH_FLOAT_TABLE_TRIGONOMETRY)
//--#pragma message "Table float trigonometry calculation in algebra classes"

#define CMATH_VEC2_FLOAT_TABLE_TRIGONOMETRY
#define CMATH_VEC3_FLOAT_TABLE_TRIGONOMETRY
#define CMATH_VEC4_FLOAT_TABLE_TRIGONOMETRY
#define CMATH_MTX33_FLOAT_TABLE_TRIGONOMETRY
#define CMATH_MTX44_FLOAT_TABLE_TRIGONOMETRY
#define CMATH_QUAT_FLOAT_TABLE_TRIGONOMETRY
#define CMATH_PLANE_FLOAT_TABLE_TRIGONOMETRY

// Default trigonometry computation
//--#else
//--#pragma message "Default float trigonometry calculation in algebra classes"
#endif // Trigonometry computation precision preprocessor

///////////////////////////////////////////////////////////////////////////////////////
// Fixed trigonometry computation defines
///////////////////////////////////////////////////////////////////////////////////////
// High precision float trigonometry computation for fixed types
// Float table trigonometry computation for fixed types
// Fixed table trigonometry computation


#endif //_MATH_LIB_DEFINES_H_
