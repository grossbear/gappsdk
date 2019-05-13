///////////////////////////////////////////////////////////////////////////////////////
//  vectorspec.cpp
//
//  Vector classes methods specialization
//
///////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

//#ifdef MATH_SSE2
#include <xmmintrin.h>
//--#include <emmintrin.h>
//--#include <immintrin.h>
#include <memory.h>
//#endif //MATH_SSE2

///////////////////////////////////////////////////////////////////////////////////////
// Vector2D
///////////////////////////////////////////////////////////////////////////////////////
#if defined(MATH_SSE2) && defined(MATH_DOUBLE_INST)
///////////////////////////////////////////////////////////////////////////////////////
// Performs A Linear Interpolation Between Two 2D Vectors
template <>
void CMVec2Lerp(CMVector2D<double> &vOut, const CMVector2D<double> &v1, const CMVector2D<double> &v2, double factor)
{
    // v1 + ((v2 - v1)*factor);
    printf("sse vector2 lerp\n");
    const double tabfact[2] = {factor,factor};
    __m128d factreg = _mm_load_pd(tabfact);
    __m128d v1reg = _mm_load_pd((const double*)v1);
    __m128d v2reg = _mm_load_pd((const double*)v2);
    
    __m128d vsubreg = _mm_sub_pd(v2reg,v1reg);
    __m128d vmulreg = _mm_mul_pd(vsubreg,factreg);
    __m128d outvreg = _mm_add_pd(v1reg,vmulreg);
    
    _mm_store_pd((double*)vOut, outvreg);
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs A Pack Operation Of All Values In 2D Vector From [-1,1] To [0,1]
template <>
void CMVec2Pack01(CMVector2D<double> &vOut, const CMVector2D<double> &vIn)
{
    const double tabvals[2] = {0.5, 0.5};
    __m128d v05reg = _mm_load_pd(tabvals);
    __m128d invreg = _mm_load_pd((const double*)vIn);
    
    //__m128d outvreg = _mm_fmadd_pd(invreg, v05reg, v05reg); --not working
    __m128d vprod = _mm_mul_pd(invreg, v05reg);
    __m128d outvreg = _mm_add_pd(vprod, v05reg);
   
    _mm_store_pd((double*)vOut, outvreg);
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs An Unpack Operation Of All Values In 2D Vector From [0,1] To [-1,1]
template <>
void CMVec2Unpack01(CMVector2D<double> &vOut, const CMVector2D<double> &vIn)
{
    const double tabvals1[2] = {1.0,1.0};
    const double tabvals2[2] = {2.0,2.0};
    __m128d v1reg = _mm_load_pd(tabvals1);
    __m128d v2reg = _mm_load_pd(tabvals2);
    
    __m128d invreg = _mm_load_pd((const double*)vIn);
    //__m128d outvreg = _mm_fmsub_pd(invreg, v2reg, v1reg);
    
    __m128d vprod = _mm_mul_pd(invreg, v2reg);
    __m128d outvreg = _mm_sub_pd(vprod, v1reg);
    
    _mm_store_pd((double*)vOut, outvreg);
}
///////////////////////////////////////////////////////////////////////////////////////
#endif //MATH_SSE2 && MATH_DOUBLE_INST

/*
///////////////////////////////////////////////////////////////////////////////////////
// Vector3D
///////////////////////////////////////////////////////////////////////////////////////
#if defined(MATH_ALGEBRA_SSE)
///////////////////////////////////////////////////////////////////////////////////////
// Performs A Linear Interpolation Between Two 3D Vectors
void CMVec3Lerp(CMVector3D<float> &vOut, const CMVector3D<float> &v1, const CMVector3D<float> &v2, float factor)
{
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs A Pack Operation Of All Values In 2D Vector From [-1,1] To [0,1]
void CMVec3Pack01(CMVector3D<float> &vOut, const CMVector3D<float> &vIn)
{
    const float tabvals[4] = {0.5f,0.5f,0.5f,0.5f};
    __m128 v05reg = _mm_load_ps(tabvals);
    __m128 invreg = _mm_set_ps(0.0f,vIn.z,vIn.y,vIn.x);
    
    
    //__m128 outvreg = _mm_fmadd_ps(invreg, halfonevreg, halfonevreg);
    __m128 vprod = _mm_mul_ps(invreg,v05reg);
    __m128 outvreg = _mm_add_ps(vprod,v05reg);
    
    float outvals[4] = {0.0f,0.0f,0.0f,0.0f};
    _mm_store_ps(outvals, outvreg);
    
    memcpy((float*)vOut, outvals, sizeof(float)*3);
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs An Unpack Operation Of All Values In 2D Vector From [0,1] To [-1,1]
void CMVec3Unpack01(CMVector3D<float> &vOut, const CMVector3D<float> &vIn)
{
    const float tabvals1[4] = {1.0f,1.0f,1.0f,1.0f};
    const float tabvals2[4] = {2.0f,2.0f,2.0f,2.0f};
    __m128 onevreg = _mm_load_ps(tabvals1);
    __m128 twovreg = _mm_load_ps(tabvals2);
    
    __m128 invreg = _mm_set_ps(0.0f,vIn.z,vIn.y,vIn.x);
    
    //__m128 outvreg = _mm_fmsub_ps(invreg, twovreg, onevreg);
    __m128 vprod = _mm_mul_ps(invreg,twovreg);
    __m128 outvreg = _mm_sub_ps(vprod,onevreg);
    
    float outvals[4] = {0.0f,0.0f,0.0f,0.0f};
    _mm_store_ps(outvals, outvreg);
    
    memcpy((float*)vOut, outvals, sizeof(float)*3);
}
///////////////////////////////////////////////////////////////////////////////////////

#if defined(MATH_DOUBLE_INST)
///////////////////////////////////////////////////////////////////////////////////////
// Performs A Linear Interpolation Between Two 3D Vectors
void CMVec3Lerp(CMVector3D<double> &vOut, const CMVector3D<double> &v1, const CMVector3D<double> &v2, double factor)
{
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs A Pack Operation Of All Values In 2D Vector From [-1,1] To [0,1]
void CMVec3Pack01(CMVector3D<double> &vOut, const CMVector3D<double> &vIn)
{
    const double tabhalf[4] = {0.5,0.5,0.5,0.5};
    __m256d v05reg = _mm256_load_pd(tabhalf);
    __m256d invreg = _mm256_set_pd(0.0,vIn.z,vIn.y,vIn.x);

    //__m256d outvreg = _mm256_fmadd_pd(invreg, v05reg, v05reg);
    __m256d vprod = _mm256_mul_pd(invreg,v05reg);
    __m256d outvreg = _mm256_add_pd(vprod,v05reg);

    double outvals[4] = {0.0, 0.0, 0.0, 0.0};
    //_mm256_store_pd(outvals, outvreg);

    memcpy(vOut, outvals, sizeof(double)*3);
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs An Unpack Operation Of All Values In 2D Vector From [0,1] To [-1,1]
void CMVec3Unpack01(CMVector3D<double> &vOut, const CMVector3D<double> &vIn)
{
    const double tabvals1[4] = {1.0,1.0,1.0,1.0};
    const double tabvals2[4] = {2.0,2.0,2.0,2.0};
    __m256d v1reg = _mm256_load_pd(tabvals1);
    __m256d v2reg = _mm256_load_pd(tabvals2);

    __m256d invreg = _mm256_set_pd(0.0,vIn.z,vIn.y,vIn.x);
    //__m256d outvreg = _mm256_fmsub_pd(invreg, v2reg, v1reg);
    __m256d vprod = _mm256_mul_pd(invreg,v2reg);
    __m256d outvreg = _mm256_sub_pd(vprod,v1reg);

    double outvals[4] = {0.0,0.0,0.0,0.0};
    //_mm256_store_pd(outvals, outvreg);

    memcpy(vOut, outvals, sizeof(double)*3);
}
#endif //MATH_DOUBLE_INST
///////////////////////////////////////////////////////////////////////////////////////
#endif //MATH_ALGEBRA_SSE


///////////////////////////////////////////////////////////////////////////////////////
// Vector4D
///////////////////////////////////////////////////////////////////////////////////////
#if defined(MATH_ALGEBRA_SSE)
///////////////////////////////////////////////////////////////////////////////////////
// Performs A Linear Interpolation Between Two 4D Vectors
void CMVec4Lerp(CMVector4D<float> &vOut, const CMVector4D<float> &v1, const CMVector4D<float> &v2, float weight)
{
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs A Pack Operation Of All Values In 2D Vector From [-1,1] To [0,1]
void CMVec4Pack01(CMVector4D<float> &vOut, const CMVector4D<float> &vIn)
{
    const float tabvals[4] = {0.5f,0.5f,0.5f,0.5f};
    __m128 v05reg = _mm_load_ps(tabvals);
    __m128 invreg = _mm_load_ps(vIn);
    
    //__m128 outvreg = _mm_fmadd_ps(invreg, halfonevreg, halfonevreg);
    __m128 vprod = _mm_mul_ps(invreg, v05reg);
    __m128 outvreg = _mm_add_ps(vprod, v05reg);
    
    _mm_store_ps((float*)vOut, outvreg);
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs An Unpack Operation Of All Values In 2D Vector From [0,1] To [-1,1]
void CMVec4Unpack01(CMVector4D<float> &vOut, const CMVector4D<float> &vIn)
{
    const float tabvals1[4] = {1.0f,1.0f,1.0f,1.0f};
    const float tabvals2[4] = {2.0f,2.0f,2.0f,2.0f};
    __m128 v1reg = _mm_load_ps(tabvals1);
    __m128 v2reg = _mm_load_ps(tabvals2);
    
    __m128 invreg = _mm_load_ps((const float*)vIn);
    //__m128 outvreg = _mm_fmsub_ps(invreg, twovreg, onevreg);
    __m128 vprod = _mm_mul_ps(invreg, v2reg);
    __m128 outvreg = _mm_sub_ps(vprod, v1reg);
    
    _mm_store_ps((float*)vOut, outvreg);
}
///////////////////////////////////////////////////////////////////////////////////////

#if defined(MATH_DOUBLE_INST)
///////////////////////////////////////////////////////////////////////////////////////
// Performs A Linear Interpolation Between Two 4D Vectors
void CMVec4Lerp(CMVector4D<double> &vOut, const CMVector4D<double> &v1, const CMVector4D<double> &v2, double factor)
{
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs A Pack Operation Of All Values In 2D Vector From [-1,1] To [0,1]
void CMVec4Pack01(CMVector4D<double> &vOut, const CMVector4D<double> &vIn)
{
    const double tabhalf[4] = {0.5,0.5,0.5,0.5};
    __m256d v05reg = _mm256_load_pd(tabhalf);
    __m256d invreg = _mm256_load_pd((const double*)vIn);
    
    //__m256d outvreg = _mm256_fmadd_pd(invreg, v05reg, v05reg);
    __m256d vprod = _mm256_mul_pd(invreg, v05reg);
    __m256d outvreg = _mm256_add_pd(vprod, v05reg);
    
    //_mm256_store_pd((double*)vOut, outvreg);
}

///////////////////////////////////////////////////////////////////////////////////////
// Performs An Unpack Operation Of All Values In 2D Vector From [0,1] To [-1,1]
void CMVec4Unpack01(CMVector4D<double> &vOut, const CMVector4D<double> &vIn)
{
    const double tabvals1[4] = {1.0,1.0,1.0,1.0};
    const double tabvals2[4] = {2.0,2.0,2.0,2.0};
    __m256d v1reg = _mm256_load_pd(tabvals1);
    __m256d v2reg = _mm256_load_pd(tabvals2);
    
    __m256d invreg = _mm256_load_pd((const double*)vIn);
    //__m256d outvreg = _mm256_fmsub_pd(invreg, v2reg, v1reg);
    __m256d vprod = _mm256_mul_pd(invreg, v2reg);
    __m256d outvreg = _mm256_sub_pd(vprod, v1reg);
    
    //_mm256_store_pd((double*)vOut, outvreg);
}
#endif //MATH_DOUBLE_INST
///////////////////////////////////////////////////////////////////////////////////////
#endif //MATH_ALGEBRA_SSE
*/


