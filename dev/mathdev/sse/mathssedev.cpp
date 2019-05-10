#include <stdio.h>
#include "base/math/mathlib.h"

///////////////////////////////////////////////////////////////////////////////////////
inline void MVEC2PACK01(float vout[2], const float vin[2])
{
    vout[0] = mpack01(vin[0]);
    vout[1] = mpack01(vin[1]);
}
///////////////////////////////////////////////////////////////////////////////////////
inline void MVEC2PACK01(double vout[2], const double vin[2])
{
#ifdef MATH_ALGEBRA_SSE
    const double tabvals[2] = {0.5, 0.5};
    __m128d v05reg = _mm_load_pd(tabvals);
    __m128d invreg = _mm_load_pd(vin);
    
    __m128d outvreg = _mm_fmadd_pd(invreg, v05reg, v05reg);
   
    _mm_store_pd(vout, outvreg);
#else
    vout[0] = mpack01(vin[0]);
    vout[1] = mpack01(vin[1]);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
inline void MVEC2UNPACK01(float vout[2], const float vin[2])
{
    vout[0] = munpack01(vin[0]);
    vout[1] = munpack01(vin[1]);
}
///////////////////////////////////////////////////////////////////////////////////////
inline void MVEC2UNPACK01(double vout[2], const double vin[2])
{
#ifdef MATH_ALGEBRA_SSE
    const double tabvals1[2] = {1.0,1.0};
    const double tabvals2[2] = {2.0,2.0};
    __m128d v1reg = _mm_load_pd(tabvals1);
    __m128d v2reg = _mm_load_pd(tabvals2);
    
    __m128d invreg = _mm_load_pd(vin);
    __m128d outvreg = _mm_fmsub_pd(invreg, v2reg, v1reg);
    
    _mm_store_pd(vout, outvreg);
#else
    vout[0] = munpack01(vin[0]);
    vout[1] = munpack01(vin[1]);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    printf("Math library sse algebra development programme\n");
    
    float vec[2] = {-0.25f, 0.5f};
    float outvec[2] = {0.0f, 0.0f};
    MVEC2PACK01(outvec, vec);
    
    printf("vec[0] = %f, vec[1] = %f\n", vec[0], vec[1]);
    printf("outvec[0] = %f, outvec[1] = %f\n", outvec[0], outvec[1]);
    
    double dvec[2] = {-0.25, 0.5};
    double doutvec[2] = {0.0, 0.0};
    MVEC2PACK01(doutvec, dvec);

    printf("double outvec[0] = %f, outvec[1] = %f\n", doutvec[0], outvec[1]);
    
    cvec2f vec1(-0.25f, 0.5f);
    cvec2f vec2 = vec1 + cvec2f(0.2f, 0.2f);
  

    return 0;
}
