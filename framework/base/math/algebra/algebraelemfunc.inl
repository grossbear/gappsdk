///////////////////////////////////////////////////////////////////////////////////////
//
//  File:     algebraelemfunc.inl
//  Content:  Inline elementary functions used in algebra classes  
//
///////////////////////////////////////////////////////////////////////////////////////

#ifndef _ALGEBRA_ELEMENTARY_FUNC_INL
#define _ALGEBRA_ELEMENTARY_FUNC_INL

#ifdef MATH_PRIM_SSE
#include <xmmintrin.h>
#include <memory.h>
#endif //MATH_PRIM_SSE

///////////////////////////////////////////////////////////////////////////////////////
// Vec2
M_FORCEINL float MVEC2SQRT(float x)
{
#ifdef CMATH_VEC2_FLOAT_TABLE_SQRT
    return m_tsqrt(x);
#elif defined (CMATH_VEC2_FAST_FLOAT_SQRT)
    return m_fsqrt(x);
#elif defined (CMATH_VEC2_HIGH_PREC_FLOAT_SQRT)
    return (float)msqrt((double)x);
#else
    return msqrt(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC2SQRT(double x)
{
    return msqrt(x);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC2SQRT(float x, float y)
{
#ifdef CMATH_VEC2_FLOAT_TABLE_SQRT
    return m_tsqrt(x*x + y*y);
#elif defined (CMATH_VEC2_FAST_FLOAT_SQRT)
    return m_fsqrt(x*x + y*y);
#elif defined (CMATH_VEC2_HIGH_PREC_FLOAT_SQRT)
    return (float)msqrt(double(x)*double(x) + double(y)*double(y));
#else 
    return msqrt(x*x + y*y);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC2SQRT(double x, double y)
{
    return msqrt(x*x + y*y);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC2REVSQRT(float x, float y)
{
    ASSERT((x*x + y*y) > FLOAT_EPS);

#ifdef CMATH_VEC2_FLOAT_TABLE_SQRT
    return 1.0f/m_tsqrt(x*x + y*y);
#elif defined(CMATH_VEC2_FAST_FLOAT_SQRT)
    return m_rfsqrt(x*x + y*y);
#elif defined(CMATH_VEC2_HIGH_PREC_FLOAT_SQRT)
    return (float)(1.0/msqrt(double(x)*double(x) + double(y)*double(y)));
#else
    return 1.0f/msqrt(x*x + y*y);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC2REVSQRT(double x, double y)
{
    ASSERT((x*x + y*y) > DOUBLE_EPS);

    return msqrt(x*x + y*y);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC2SINCOS(float angle, float &sina, float &cosa)
{
#ifdef CMATH_VEC2_FLOAT_TABLE_TRIGONOMETRY
    m_tsincosf(angle,sina,cosa);
#elif defined (MATH_VEC2_HIGH_PREC_FLOAT_TRIGONOMETRY)
    double dsina, dcosa;
    msincos((double)angle,dsina,dcosa);
    sina = (float)dsina;
    cosa = (float)dcosa;
#else
    msincos(angle,sina,cosa);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC2SINCOS(double angle, double &sina, double &cosa)
{
    msincos(angle,sina,cosa);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC2COS(float angle)
{
#ifdef CMATH_VEC2_FLOAT_TABLE_TRIGONOMETRY
    return m_tcosf(angle);
#elif defined (CMATH_VEC2_HIGH_PREC_FLOAT_TRIGONOMETRY)
    return (float)mcos((double)angle);
#else
    return mcos(angle);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC2COS(double angle)
{
    return mcos(angle);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC2ACOS(float x)
{
#ifdef CMATH_VEC2_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)macos((double)x);
#else
    return macos(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC2ACOS(double x)
{
    return macos(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC2PACK01(float vout[2], const float vin[2])
{
    vout[0] = mpack01(vin[0]);
    vout[1] = mpack01(vin[1]);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC2PACK01(double vout[2], const double vin[2])
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
M_FORCEINL void MVEC2UNPACK01(float vout[2], const float vin[2])
{
    vout[0] = munpack01(vin[0]);
    vout[1] = munpack01(vin[1]);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC2UNPACK01(double vout[2], const double vin[2])
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


///////////////////////////////////////////////////////////////////////////////////////
// Vec3
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC3SQRT(float x)
{
#ifdef CMATH_VEC3_FLOAT_TABLE_SQRT
    return m_tsqrt(x);
#elif defined(CMATH_VEC3_FAST_FLOAT_SQRT)
    return m_fsqrt(x);
#elif defined(CMATH_VEC3_HIGH_PREC_FLOAT_SQRT)
    return (float)msqrt((double)x);
#else
    return msqrt(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC3SQRT(double x)
{
    return msqrt(x);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC3SQRT(float x, float y, float z)
{
#ifdef CMATH_VEC3_FLOAT_TABLE_SQRT
    return m_tsqrt(x*x + y*y + z*z);
#elif defined(CMATH_VEC3_FAST_FLOAT_SQRT)
    return m_fsqrt(x*x + y*y + z*z);
#elif defined(CMATH_VEC3_HIGH_PREC_FLOAT_SQRT)
    double xd(x),yd(y),zd(z);
    return (float)msqrt(xd*xd + yd*yd + zd*zd);
#else 
    return msqrt(x*x + y*y + z*z);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC3SQRT(double x, double y, double z)
{
    return msqrt(x*x + y*y + z*z);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC3REVSQRT(float x, float y, float z)
{
    ASSERT((x*x + y*y + z*z) > FLOAT_EPS);

#ifdef CMATH_VEC3_FLOAT_TABLE_SQRT
    return 1.0f/m_tsqrt(x*x + y*y + z*z);
#elif defined(CMATH_VEC3_FAST_FLOAT_SQRT)
    return m_rfsqrt(x*x + y*y + z*z);
#elif defined(CMATH_VEC3_HIGH_PREC_FLOAT_SQRT)
    double xd(x),yd(y),zd(z);
    return (float)(1.0/msqrt(xd*xd + yd*yd + zd*zd));
#else
    return 1.0f/msqrt(x*x + y*y + z*z);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC3REVSQRT(double x, double y, double z)
{
    ASSERT((x*x + y*y + z*z) > DOUBLE_EPS);

    return 1.0f/msqrt(x*x + y*y + z*z);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC3SINCOS(float angle, float &sina, float &cosa)
{
#ifdef CMATH_VEC3_FLOAT_TABLE_TRIGONOMETRY
    m_tsincosf(angle,sina,cosa);
#elif defined (CMATH_VEC3_HIGH_PREC_FLOAT_TRIGONOMETRY)
    double dsina,dcosa;
    msincos((double)angle,dsina,dcosa);
    sina = (float)dsina;
    cosa = (float)dcosa;
#else
    msincos(angle,sina,cosa);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC3SINCOS(double angle, double &sina, double &cosa)
{
    msincos(angle,sina,cosa);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC3COS(float angle)
{
#ifdef CMATH_VEC3_FLOAT_TABLE_TRIGONOMETRY
    return m_tcosf(angle);
#elif defined (CMATH_VEC3_HIGH_PREC_FLOAT_TRIGONOMETRY)
    return (float)mcos((double)angle);
#else
    return mcos(angle);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC3COS(double angle)
{
    return mcos(angle);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC3ACOS(float x)
{
#ifdef CMATH_VEC3_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)macos((double)x);
#else
    return macos(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC3ACOS(double x)
{
    return macos(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC3PACK01(float vout[3], const float vin[3])
{
#ifdef MATH_ALGEBRA_SSE
    const float tabvals[4] = {0.5f,0.5f,0.5f,0.5f};
    __m128 halfonevreg = _mm_load_ps(tabvals);
    __m128 invreg = _mm_set_ps(0.0f,vin[2],vin[1],vin[0]);
    
    __m128 outvreg = _mm_fmadd_ps(invreg, halfonevreg, halfonevreg);
    
    float outvals[4] = {0.0f,0.0f,0.0f,0.0f};
    _mm_store_ps(outvals, outvreg);
    
    memcpy(vout, outvals, sizeof(float)*3);
#else
    vout[0] = mpack01(vin[0]);
    vout[1] = mpack01(vin[1]);
    vout[2] = mpack01(vin[2]);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC3PACK01(double vout[3], const double vin[3])
{
#ifdef MATH_ALGEBRA_SSE
    const double tabhalf[4] = {0.5,0.5,0.5,0.5};
    __m256d v05reg = _mm256_load_pd(tabhalf);
    __m256d invreg = _mm256_set_pd(0.0,vin[2],vin[1],vin[0]);
    
    __m256d outvreg = _mm256_fmadd_pd(invreg, v05reg, v05reg);
    
    double outvals[4] = {0.0, 0.0, 0.0, 0.0};
    _mm256_store_pd(outvals, outvreg);
    
    memcpy(vout, outvals, sizeof(double)*3);
#else
    vout[0] = mpack01(vin[0]);
    vout[1] = mpack01(vin[1]);
    vout[2] = mpack01(vin[2]);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC3UNPACK01(float vout[3], const float vin[3])
{
#ifdef MATH_ALGEBRA_SSE
    const float tabvals1[4] = {1.0f,1.0f,1.0f,1.0f};
    const float tabvals2[4] = {2.0f,2.0f,2.0f,2.0f};
    __m128 onevreg = _mm_load_ps(tabvals1);
    __m128 twovreg = _mm_load_ps(tabvals2);
    
    __m128 invreg = _mm_set_ps(0.0f,vin[2],vin[1],vin[0]);
    __m128 outvreg = _mm_fmsub_ps(invreg, twovreg, onevreg);
    
    float outvals[4] = {0.0f,0.0f,0.0f,0.0f};
    _mm_store_ps(outvals, outvreg);
    
    memcpy(vout, outvals, sizeof(float)*3);
#else
    vout[0] = munpack01(vin[0]);
    vout[1] = munpack01(vin[1]);
    vout[2] = munpack01(vin[2]);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC3UNPACK01(double vout[3], const double vin[3])
{
#ifdef MATH_ALGEBRA_SSE
    const double tabvals1[4] = {1.0,1.0,1.0,1.0};
    const double tabvals2[4] = {2.0,2.0,2.0,2.0};
    __m256d v1reg = _mm256_load_pd(tabvals1);
    __m256d v2reg = _mm256_load_pd(tabvals2);
    
    __m256d invreg = _mm256_set_pd(0.0,vin[2],vin[1],vin[0]);
    __m256d outvreg = _mm256_fmsub_pd(invreg, v2reg, v1reg);
    
    double outvals[4] = {0.0,0.0,0.0,0.0};
    _mm256_store_pd(outvals, outvreg);
    
    memcpy(vout, outvals, sizeof(double)*3);
#else
    vout[0] = munpack01(vin[0]);
    vout[1] = munpack01(vin[1]);
    vout[2] = munpack01(vin[2]);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////
// Vec4
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC4SQRT(float x)
{
#ifdef CMATH_VEC4_FLOAT_TABLE_SQRT
    return m_tsqrt(x);
#elif defined(CMATH_VEC4_FAST_FLOAT_SQRT)
    return m_fsqrt(x);
#elif defined(CMATH_VEC4_HIGH_PREC_FLOAT_SQRT)
    return (float)msqrt((double)x);
#else
    return msqrt(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC4SQRT(double x)
{
    return msqrt(x);
}

M_FORCEINL float MVEC4SQRT(float x, float y, float z, float w)
{
#ifdef CMATH_VEC4_FLOAT_TABLE_SQRT
    return m_tsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_VEC4_FAST_FLOAT_SQRT)
    return m_fsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_VEC4_HIGH_PREC_FLOAT_SQRT)
    double xd(x),yd(y),zd(z),wd(w);
    return (float)msqrt(xd*xd + yd*yd + zd*zd + wd*wd);
#else 
    return msqrt(x*x + y*y + z*z + w*w);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC4SQRT(double x, double y, double z, double w)
{
    return msqrt(x*x + y*y + z*z + w*w);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC4REVSQRT(float x, float y, float z, float w)
{
    ASSERT((x*x + y*y + z*z + w*w) > FLOAT_EPS);

#ifdef CMATH_VEC4_FLOAT_TABLE_SQRT
    return 1.0f/m_tsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_VEC4_FAST_FLOAT_SQRT)
    return m_rfsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_VEC4_HIGH_PREC_FLOAT_SQRT)
    double xd(x),yd(y),zd(z),wd(w);
    return (float)(1.0/msqrt(xd*xd + yd*yd + zd*zd + wd*wd));
#else
    return 1.0f/msqrt(x*x + y*y + z*z + w*w);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC4REVSQRT(double x, double y, double z, double w)
{
    ASSERT((x*x + y*y + z*z + w*w) > DOUBLE_EPS);

    return msqrt(x*x + y*y + z*z + w*w);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC4SINCOS(float angle, float &sina, float &cosa)
{
#ifdef CMATH_VEC4_FLOAT_TABLE_TRIGONOMETRY
    m_tsincosf(angle,sina,cosa);
#elif defined (CMATH_VEC4_HIGH_PREC_FLOAT_TRIGONOMETRY)
    double dsina, dcosa;
    msincos((double)angle,dsina,dcosa);
    sina = (float)dsina;
    cosa = (float)dcosa;
#else
    msincos(angle,sina,cosa);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC4SINCOS(double angle, double &sina, double &cosa)
{
    msincos(angle,sina,cosa);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC4COS(float angle)
{
#ifdef CMATH_VEC4_FLOAT_TABLE_TRIGONOMETRY
    return m_tcosf(angle);
#elif defined (CMATH_VEC4_HIGH_PREC_FLOAT_TRIGONOMETRY)
    return (float)mcos((double)angle);
#else
    return mcos(angle);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC4COS(double angle)
{
    return mcos(angle);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MVEC4ACOS(float x)
{
#ifdef CMATH_VEC4_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)macos((double)x);
#else
    return macos(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MVEC4ACOS(double x)
{
    return macos(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC4PACK01(float vout[4], const float vin[4])
{
#ifdef MATH_ALGEBRA_SSE
    const float tabvals[4] = {0.5f,0.5f,0.5f,0.5f};
    __m128 halfonevreg = _mm_load_ps(tabvals);
    __m128 invreg = _mm_load_ps(vin);
    
    __m128 outvreg = _mm_fmadd_ps(invreg, halfonevreg, halfonevreg);
    
    _mm_store_ps(vout, outvreg);
#else
    vout[0] = mpack01(vin[0]);
    vout[1] = mpack01(vin[1]);
    vout[2] = mpack01(vin[2]);
    vout[3] = mpack01(vin[3]);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC4PACK01(double vout[4], const double vin[4])
{
#ifdef MATH_ALGEBRA_SSE
    const double tabhalf[4] = {0.5,0.5,0.5,0.5};
    __m256d v05reg = _mm256_load_pd(tabhalf);
    __m256d invreg = _mm256_set_pd(0.0,vin[2],vin[1],vin[0]);
    
    __m256d outvreg = _mm256_fmadd_pd(invreg, v05reg, v05reg);
    
    _mm256_store_pd(vout, outvreg);
#else
    vout[0] = mpack01(vin[0]);
    vout[1] = mpack01(vin[1]);
    vout[2] = mpack01(vin[2]);
    vout[3] = mpack01(vin[3]);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC4UNPACK01(float vout[4], const float vin[4])
{
#ifdef MATH_ALGEBRA_SSE
    const float tabvals1[4] = {1.0f,1.0f,1.0f,1.0f};
    const float tabvals2[4] = {2.0f,2.0f,2.0f,2.0f};
    __m128 onevreg = _mm_load_ps(tabvals1);
    __m128 twovreg = _mm_load_ps(tabvals2);
    
    __m128 invreg = _mm_load_ps(vin);
    __m128 outvreg = _mm_fmsub_ps(invreg, twovreg, onevreg);
    
    _mm_store_ps(vout, outvreg);
#else
    vout[0] = munpack01(vin[0]);
    vout[1] = munpack01(vin[1]);
    vout[2] = munpack01(vin[2]);
    vout[3] = munpack01(vin[3]);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MVEC4UNPACK01(double vout[4], const double vin[4])
{
#ifdef MATH_ALGEBRA_SSE
    const double tabvals1[4] = {1.0,1.0,1.0,1.0};
    const double tabvals2[4] = {2.0,2.0,2.0,2.0};
    __m256d v1reg = _mm256_load_pd(tabvals1);
    __m256d v2reg = _mm256_load_pd(tabvals2);
    
    __m256d invreg = _mm256_load_pd(vin);
    __m256d outvreg = _mm256_fmsub_pd(invreg, v2reg, v1reg);
    
    _mm256_store_pd(vout, outvreg);
#else
    vout[0] = munpack01(vin[0]);
    vout[1] = munpack01(vin[1]);
    vout[2] = munpack01(vin[2]);
    vout[3] = munpack01(vin[3]);
#endif
}

///////////////////////////////////////////////////////////////////////////////////////
// Plane
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MPLANESQRT(float a, float b, float c)
{
#ifdef CMATH_PLANE_FLOAT_TABLE_SQRT
    return m_tsqrt(a*a + b*b + c*c);
#elif defined (CMATH_PLANE_FAST_FLOAT_SQRT)
    return m_fsqrt(a*a + b*b + c*c);
#elif defined (CMATH_PLANE_HIGH_PREC_FLOAT_SQRT)
    double ad(a), bd(b), cd(c);
    return (float)msqrt((double)(ad*ad + bd*bd + cd*cd));
#else
    return msqrt(a*a + b*b + c*c);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MPLANESQRT(double a, double b, double c)
{
    return msqrt(a*a + b*b + c*c);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MPLANEREVSQRT(float a, float b, float c)
{
#ifdef CMATH_PLANE_FLOAT_TABLE_SQRT
    return 1.0f/m_tsqrt(a*a + b*b + c*c);
#elif defined(CMATH_PLANE_FAST_FLOAT_SQRT)
    return m_rfsqrt(a*a + b*b + c*c);
#elif defined(CMATH_PLANE_HIGH_PREC_FLOAT_SQRT)
    double ad(a), bd(b), cd(c);
    return (float)(1.0/msqrt(ad*ad + bd*bd + cd*cd));
#else
    return 1.0f/msqrt(a*a + b*b + c*c);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MPLANEREVSQRT(double a, double b, double c)
{
    return 1.0/msqrt(a*a + b*b + c*c);
}

///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Matrix3x3
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MMTX33SINCOS(float angle, float &sina, float &cosa)
{
#ifdef CMATH_MTX33_FLOAT_TABLE_TRIGONOMETRY
    m_tsincosf(angle,sina,cosa);
#elif defined (CMATH_MTX33_HIGH_PREC_FLOAT_TRIGONOMETRY)
    double dsina, dcosa;
    msincos((double)angle,dsina,dcosa);
    sina = (float)dsina;
    cosa = (float)dcosa;
#else
    msincos(angle,sina,cosa);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MMTX33SINCOS(double angle, double &sina, double &cosa)
{
    msincos(angle,sina,cosa);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MMTX33SQRT(float x, float y, float z)
{
#ifdef CMATH_MTX33_FLOAT_TABLE_SQRT
    return m_tsqrt(x*x + y*y + z*z);
#elif defined(CMATH_MTX33_FAST_FLOAT_SQRT)
    return m_fsqrt(x*x + y*y + z*z);
#elif defined(CMATH_MTX33_HIGH_PREC_FLOAT_SQRT)
    double xd(x), yd(y), zd(z);
    return (float)msqrt(xd*xd + yd*yd + zd*zd);
#else
    return msqrt(x*x + y*y + z*z);
#endif 
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MMTX33SQRT(double x, double y, double z)
{
    return msqrt(x*x + y*y + z*z);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MMTX33ASIN(float x)
{
#ifdef CMATH_MTX33_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)masin((double)x);
#else
    return masin(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MMTX33ASIN(double x)
{
    return masin(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MMTX33ATAN2(float y, float x)
{
#ifdef CMATH_MTX33_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)matan2((double)y,(double)x);
#else
    return matan2(y,x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MMTX33ATAN2(double y, double x)
{
    return matan2(y,x);
}

///////////////////////////////////////////////////////////////////////////////////////
// Matrix4x4
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MMTX44SINCOS(float angle, float &sina, float &cosa)
{
#ifdef CMATH_MTX44_FLOAT_TABLE_TRIGONOMETRY
    m_tsincosf(angle,sina,cosa);
#elif defined (CMATH_MTX44_HIGH_PREC_FLOAT_TRIGONOMETRY)
    double dsina, dcosa;
    msincos((double)angle,dsina,dcosa);
    sina = (float)dsina;
    cosa = (float)dcosa;
#else
    msincos(angle,sina,cosa);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MMTX44SINCOS(double angle, double &sina, double &cosa)
{
    msincos(angle,sina,cosa);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MMTX44SQRT(float x, float y, float z)
{
#ifdef CMATH_MTX44_FLOAT_TABLE_SQRT
    return m_tsqrt(x*x + y*y + z*z);
#elif defined(CMATH_MTX44_FAST_FLOAT_SQRT)
    return m_fsqrt(x*x + y*y + z*z);
#elif defined(CMATH_MTX44_HIGH_PREC_FLOAT_SQRT)
    double xd(x), yd(y), zd(z);
    return (float)msqrt(xd*xd + yd*yd + zd*zd);
#else
    return msqrt(x*x + y*y + z*z);
#endif 
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MMTX44SQRT(double x, double y, double z)
{
    return msqrt(x*x + y*y + z*z);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MMTX44ASIN(float x)
{
#ifdef CMATH_MTX44_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)masin((double)x);
#else
    return masin(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MMTX44ASIN(double x)
{
    return masin(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MMTX44ATAN2(float y, float x)
{
#ifdef CMATH_MTX44_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)matan2((double)y,(double)x);
#else
    return matan2(y,x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MMTX44ATAN2(double y, double x)
{
    return matan2(y,x);
}

///////////////////////////////////////////////////////////////////////////////////////
// Quaternion
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MQUATSINCOS(float angle, float &sina, float &cosa)
{
#ifdef CMATH_QUAT_FLOAT_TABLE_TRIGONOMETRY
    m_tsincosf(angle,sina,cosa);
#elif defined (CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY)
    double dsina, dcosa;
    msincos((double)angle,dsina,dcosa);
    sina = (float)dsina;
    cosa = (float)dcosa;
#else
    msincos(angle,sina,cosa);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL void MQUATSINCOS(double angle, double &sina, double &cosa)
{
    msincos(angle,sina,cosa);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATATAN2(float y, float x)
{
#ifdef CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)matan2((double)y,(double)x);
#else
    return matan2(y,x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATATAN2(double y, double x)
{
    return matan2(y,x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATATAN(float x)
{
#ifdef CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)matan((double)x);
#else
    return matan(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATATAN(double x)
{
    return matan(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATSIN(float x)
{
#ifdef CMATH_QUAT_FLOAT_TABLE_TRIGONOMETRY
    return m_tsinf(x);
#elif defined (CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY)
    return (float)msin((double)x);
#else
    return msin(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATSIN(double x)
{
    return msin(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATASIN(float x)
{
#ifdef CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)msin((double)x);
#else
    return msin(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATASIN(double x)
{
    return msin(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATACOS(float x)
{
#ifdef CMATH_QUAT_HIGH_PREC_FLOAT_TRIGONOMETRY
    return (float)macos((double)x);
#else
    return macos(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATACOS(double x)
{
    return macos(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATSQRT(float x, float y, float z, float w)
{
#ifdef CMATH_QUAT_FAST_FLOAT_SQRT
    return m_fsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_QUAT_FLOAT_TABLE_SQRT)
    return m_tsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_QUAT_HIGH_PREC_FLOAT_SQRT)
    double xd(x), yd(y), zd(z), wd(w);
    return (float)msqrt(xd*xd + yd*yd + zd*zd + wd*wd);
#else
    return msqrt(x*x + y*y + z*z + w*w);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATSQRT(double x, double y, double z, double w)
{
    return msqrt(x*x + y*y + z*z + w*w);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATSQRT(float x, float y, float z)
{
#ifdef CMATH_QUAT_FAST_FLOAT_SQRT
    return m_fsqrt(x*x + y*y + z*z);
#elif defined(CMATH_QUAT_FLOAT_TABLE_SQRT)
    return m_tsqrt(x*x + y*y + z*z);
#elif defined(CMATH_QUAT_HIGH_PREC_FLOAT_SQRT)
    double xd(x), yd(y), zd(z);
    return (float)msqrt(xd*xd + yd*yd + zd*zd);
#else
    return msqrt(x*x + y*y + z*z);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATSQRT(double x, double y, double z)
{
    return msqrt(x*x + y*y + z*z);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATSQRT(float x)
{
#ifdef CMATH_QUAT_FAST_FLOAT_SQRT
    return m_fsqrt(x);
#elif defined(CMATH_QUAT_FLOAT_TABLE_SQRT)
    return m_tsqrt(x);
#elif defined(CMATH_QUAT_HIGH_PREC_FLOAT_SQRT)
    return (float)msqrt(double(x));
#else
    return msqrt(x);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATSQRT(double x)
{
    return msqrt(x);
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float MQUATREVSQRT(float x, float y, float z, float w)
{
#ifdef CMATH_QUAT_FAST_FLOAT_SQRT
    return m_rfsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_QUAT_FLOAT_TABLE_SQRT)
    return 1.0f/m_tsqrt(x*x + y*y + z*z + w*w);
#elif defined(CMATH_QUAT_HIGH_PREC_FLOAT_SQRT)
    double xd(x), yd(y), zd(z), wd(w);
    return (float)(1.0/msqrt(xd*xd + yd*yd + zd*zd + wd*wd));
#else
    return 1.0f/msqrt(x*x + y*y + z*z + w*w);
#endif
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double MQUATREVSQRT(double x, double y, double z, double w)
{
    return 1.0/msqrt(x*x + y*y + z*z + w*w);
}
///////////////////////////////////////////////////////////////////////////////////////

#endif //_ALGEBRA_ELEMENTARY_FUNC_INL
