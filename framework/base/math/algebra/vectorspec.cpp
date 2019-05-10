///////////////////////////////////////////////////////////////////////////////////////
//  vectorspec.cpp
//
//  Vector classes methods specialization
//
///////////////////////////////////////////////////////////////////////////////////////

#include <xmmintrin.h>
//#include <emmintrin.h>
#include <immintrin.h>
#include <memory.h>

#ifdef MATH_DOUBLE_INST
///////////////////////////////////////////////////////////////////////////////////////
// Performs A Pack Operation Of All Values In 2D Vector From [-1,1] To [0,1]

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

#endif //MATH_DOUBLE_INST



/*
///////////////////////////////////////////////////////////////////////////////////////
#ifdef MATH_PRIM_SSE
void mpack01(float out[], const float in[], int32t size)
{
    if(size <= 0)
        return ;
    int32t endsize = size%4;
    int32t nsize = (size%4) ? (size - endsize) : (size);
    int32t i = 0;
    __m128 mhalfone = _mm_set_ps(0.5f,0.5f,0.5f,0.5f);
    if(size >= 4)
    for(i = 0; i < nsize; i+=4)
    {
        __m128 mvals = _mm_loadu_ps(&in[i]);
        __m128 melem1 = _mm_mul_ps(mvals,mhalfone);
        __m128 mres = _mm_add_ps(melem1,mhalfone);
        _mm_store_ps(&out[i],mres);
    }
    for(int32t j = 0; j < endsize; j++)
    {
        __m128 mval = _mm_set_ss(in[i+j]);
        __m128 melem2 = _mm_mul_ps(mval,mhalfone);
        __m128 mres = _mm_add_ps(melem2,mhalfone);
        _mm_store_ss(&out[i+j],mres);
    }
}
#else
void  mpack01(float out[], const float in[], int32t size)
{
    if(size <= 0)
        return ;
    for(int32t i = 0; i < size; i++)
    {
        out[i] = mpack01(in[i]);
    }
}
#endif
///////////////////////////////////////////////////////////////////////////////////////
#ifdef MATH_PRIM_SSE
void   mpack01(float &xout, float &yout, float &zout, float xin, float yin, float zin)
{
    __m128 mhalfone = _mm_set_ps(0.5f,0.5f,0.5f,0.5f);
    __m128 mvals = _mm_set_ps(0.0f,zin,yin,xin);
    __m128 melem = _mm_mul_ps(mvals,mhalfone);
    __m128 mres = _mm_add_ps(melem,mhalfone);
    float fres[4] = {0};
    _mm_store_ps(fres,mres);
    xout = fres[0];
    yout = fres[1];
    zout = fres[2];
}
#else
void   mpack01(float &xout, float &yout, float &zout, float xin, float yin, float zin)
{
    xout = mpack01(xin);
    yout = mpack01(yin);
    zout = mpack01(zin);
}
#endif
///////////////////////////////////////////////////////////////////////////////////////
#ifdef MATH_PRIM_SSE
void   mpack01_3(float out[], const float in[])
{
    __m128 mhalfone = _mm_set_ps(0.5f,0.5f,0.5f,0.5f);
    __m128 mvals = _mm_set_ps(0.0f,in[2],in[1],in[0]);
    __m128 melem = _mm_mul_ps(mvals,mhalfone);
    __m128 mres = _mm_add_ps(melem,mhalfone);
    float fres[4] = {0};
    _mm_store_ps(fres,mres);
    memcpy(&out[0],&fres[0],sizeof(float)*3);
}
#else
void   mpack01_3(float out[], const float in[])
{
    out[0] = mpack01(in[0]);
    out[1] = mpack01(in[1]);
    out[2] = mpack01(in[2]);
}
#endif
///////////////////////////////////////////////////////////////////////////////////////
#ifdef MATH_PRIM_SSE
void munpack01(float out[], const float in[], int32t size)
{
    if(size <= 0)
        return ;
    int32t endsize = size%4;
    int32t nsize = (size%4) ? (size - endsize) : (size);
    int32t i = 0;
    __m128 mtwo = _mm_set_ps(2.f,2.f,2.f,2.f);
    __m128 mone = _mm_set_ps(1.f,1.f,1.f,1.f);
    if(size >= 4)
    for(i = 0; i < nsize; i+=4)
    {
        __m128 mvals = _mm_loadu_ps(&in[i]);
        __m128 melem1 = _mm_mul_ps(mvals,mtwo);
        __m128 mres = _mm_sub_ps(melem1,mone);
        _mm_store_ps(&out[i],mres);
    }
    for(int32t j = 0; j < endsize; j++)
    {
        __m128 mval = _mm_set_ss(in[i+j]);
        __m128 melem2 = _mm_mul_ps(mval,mtwo);
        __m128 mres = _mm_add_ps(melem2,mone);
        _mm_store_ss(&out[i+j],mres);
    }
}
#else
void munpack01(float out[], const float in[], int32t size)
{
    if(size <= 0)
        return ;
    for(int32t i = 0; i < size; i++)
        out[i] = munpack01(in[i]); 
}
#endif
///////////////////////////////////////////////////////////////////////////////////////
#ifdef MATH_PRIM_SSE
void munpack01(float &xout, float &yout, float &zout, float xin, float yin, float zin)
{
    __m128 mone = _mm_set_ps(1.f,1.f,1.f,1.f);
    __m128 mtwo = _mm_set_ps(2.f,2.f,2.f,2.f);
    __m128 mvals = _mm_set_ps(0.0f,zin,yin,xin);
    __m128 melem = _mm_mul_ps(mvals,mtwo);
    __m128 mres = _mm_sub_ps(melem,mone);
    float fres[4] = {0};
    _mm_store_ps(fres,mres);
    xout = fres[0];
    yout = fres[1];
    zout = fres[2];
}
#else
void munpack01(float &xout, float &yout, float &zout, float xin, float yin, float zin)
{
    xout = munpack01(xin);
    yout = munpack01(yin);
    zout = munpack01(zin);
}
#endif
///////////////////////////////////////////////////////////////////////////////////////
#ifdef MATH_PRIM_SSE
void munpack01_3(float out[], const float in[])
{
    __m128 mtwo = _mm_set_ps(2.f,2.f,2.f,2.f);
    __m128 mone = _mm_set_ps(1.f,1.f,1.f,1.f);
    __m128 mvals = _mm_set_ps(0.0f,in[2],in[1],in[0]);
    __m128 melem = _mm_mul_ps(mvals,mtwo);
    __m128 mres = _mm_sub_ps(melem,mone);
    float fres[4] = {0};
    _mm_store_ps(fres,mres);
    memcpy(&out[0],&fres[0],sizeof(float)*3);
}
#else
void munpack01_3(float out[], const float in[])
{
    out[0] = munpack01(in[0]);
    out[1] = munpack01(in[1]);
    out[2] = munpack01(in[2]);
}
#endif
///////////////////////////////////////////////////////////////////////////////////////
*/

