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
#define MATH_PRIM_SSE

// Library Uses It's Own Conversion From Floating Point Number To Integer And Vice-Versa
//#define MATH_NO_FPU

// Library Uses ILM Functions In Converting Float Types Into Half Type
#define MATH_ILM_HALF_CONVERSION

// Build Classes Instantiation Using Following Data Types  
#define MATH_DOUBLE_INST
//#define MATH_LONG_DOUBLE_INST
//#define MATH_FIXED_INST
//#define MATH_HALF_INST


///////////////////////////////////////////////////////////////////////////////////////
// Square root computation precision preprocessor
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

// Table float square root computation
#elif defined (MATH_FLOAT_TABLE_SQRT)
//--#pragma message "Table float square root calculation in algebra classes"
#define CMATH_VEC2_FLOAT_TABLE_SQRT
#define CMATH_VEC3_FLOAT_TABLE_SQRT
#define CMATH_VEC4_FLOAT_TABLE_SQRT
#define CMATH_MTX33_FLOAT_TABLE_SQRT
#define CMATH_MTX44_FLOAT_TABLE_SQRT
#define CMATH_QUAT_FLOAT_TABLE_SQRT
#define CMATH_PLANE_FLOAT_TABLE_SQRT

// Fast approximationn float square root computation
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
// Trigonometry computation precision preprocessor
///////////////////////////////////////////////////////////////////////////////////////
// High precision trigonometry computation
#if defined (MATH_HIGH_PREC_FLOAT_TRIGONOMETRY)
//--#pragma message "High precision float trigonometry calculation in algebra classes"

#define CMATH_VEC2_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_VEC3_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_VEC4_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_MTX33_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_MTX44_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY
#define CMATH_PLANE_HIGH_PREC_FLOAT_TRIGONOMETRY

// Table trigonometry computation
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



#endif //_MATH_LIB_DEFINES_H_
