//////////////////////////////////////////////////////////////////////////////
//
//  File:       elemfunc.inl
//  Content:    Math elementary inline functions
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __ELEMFUNC_INL__
#define __ELEMFUNC_INL__

///////////////////////////////////////////////////////////////////////////////////////
// Converting Functions From Integer To Float Type And Vice Versa
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Software Conversion Functions 
M_API float     mitof(int32t i);
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    mftoi(float f);
///////////////////////////////////////////////////////////////////////////////////////

M_FORCEINL float mtoreal(int32t i)
{
#ifdef MATH_NO_FPU
    return mitof(i);
#else
    return (float)i;
#endif // MATH_NO_FPU
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL int32t mtoint(float f)
{
#ifdef MATH_NO_FPU
    return mftoi(f);
#else
    return (int32t)f;
#endif // MATH_NO_FPU
}

///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double mtoreal(int64t i)
{
#ifdef MATH_NO_FPU
    return mitof(i);
#else
    return (float)i;
#endif // MATH_NO_FPU
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL int64t mtoint(double d)
{
#ifdef MATH_NO_FPU
    return mftoi(d);
#else
    return (int64t)d;
#endif // MATH_NO_FPU
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Absolute Value Functions
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
M_INLINE Ttype  mabs(Ttype i)
{
    return (i >> (sizeof(Ttype)-1)) ? ((~i)+1) : (i);
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float  mabs(float f)
{
    return *(float*)&(*(int32t*)&f &= MATH_INT_MAX);
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double mabs(double d)
{
    return *(double*)&(*(int64t*)&d &= MATH_INT64_MAX);
}

///////////////////////////////////////////////////////////////////////////////////////
// Negate Values
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float  mnegate(float f)
{
    return *(float*)&(*(int32t*)&f ^= MATH_INT_MIN);
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double mnegate(double d)
{
    return *(double*)&(*(int64t*)&d ^= MATH_INT64_MIN);
}


///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool  mnear0(float f)
{
    return mabs(f) < FLOAT_EPS;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool  mnear0(double d)
{
    return mabs(d) < DOUBLE_EPS;
}

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Greater Than 0
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mgre0(float f)
{
    return *(int32t*)&f > 0;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mgre0(double d)
{
    return *(int64t*)&d > 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Greater Or Equals Zero
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mgreq0(float f)
{
    return *(uint32t*)&f <= 0x80000000UL;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mgreq0(double d)
{
    return *(uint64t*)&d <= 0x8000000000000000UL;
}

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Equals Zero
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mis0(float f)
{
    return (*(int32t*)&f & MATH_INT_MAX) == 0;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mis0(double d)
{
    return (*(int64t*)&d & MATH_INT64_MAX) == 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Less Or Equals Zero
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mlesseq0(float f)
{
    return *(int32t*)&f <= 0;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mlesseq0(double d)
{
    return *(int64t*)&d <= 0;
}

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Less Than 0
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mless0(float f)
{
    return *(int32t*)&f < 0;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE bool mless0(double d)
{
    return *(int64t*)&d < 0;
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Clamp Float Value To 0
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float mclamp0(float f)
{
    int32t s = (*(int32t*)&f) >> 31;
    s = ~s;
    *(int32t*)&f &= s;

    return f;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double mclamp0(double d)
{
    int64t s = (*(int64t*)&d) >> 63;
    s = ~s;
    *(int64t*)&d &= s;

    return d;
}

///////////////////////////////////////////////////////////////////////////////////////
// Clamp Float Value To 1
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float mclamp1(float f)
{
    return *(int32t*)&f > 0x3f800000 ? 1.0f : f;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double mclamp1(double d)
{
    return *(int64t*)&d > 0x3ff0000000000000 ? 1.0 : d;
}

///////////////////////////////////////////////////////////////////////////////////////
// Clamp Float Value To [0,1]
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float mclamp01(float f)
{
    if(mless0(f))
        return 0.0f;

    return mclamp1(f);
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double mclamp01(double d)
{
    if(mless0(d))
        return 0.0;

    return mclamp1(d);
}


///////////////////////////////////////////////////////////////////////////////////////
// Function Template Clamping Value
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
M_INLINE Ttype  mclamp(const Ttype &min, const Ttype &max, const Ttype &val)
{
    return (val < min) ? (min) : ((val > max) ? max : val);
}



///////////////////////////////////////////////////////////////////////////////////////
// Check If Number Is Power Of 2
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
M_INLINE bool mispow2(Ttype n)
{
    return !(n & (n - 1));
}

///////////////////////////////////////////////////////////////////////////////////////
// Set To Zero If Value Is Near 
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float   malign0(float x)
{
    if((x > -FLOAT_EPS) && (x < FLOAT_EPS))
        return 0.0f;
    else
        return x;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double  malign0(double x)
{
    if((x > -DOUBLE_EPS) && (x < DOUBLE_EPS))
        return 0.0;
    else
        return x;
}

///////////////////////////////////////////////////////////////////////////////////////
// Set To One If Value Is Nearly One
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float   malign1(float x)
{
    if( (x > (1.0f-FLOAT_EPS)) && (x < (1.0f+FLOAT_EPS)) )
        return 1.0f;
    else
        return x;
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double  malign1(double x)
{
    if( (x > (1.0-DOUBLE_EPS)) && (x < (1.0+DOUBLE_EPS)) )
        return 1.0;
    else
        return x;
}

///////////////////////////////////////////////////////////////////////////////////////
// Calculates The Floor Of A Value x
///////////////////////////////////////////////////////////////////////////////////////

M_FORCEINL float   mfloor(float x)
{
    return floorf(x);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  mfloor(double x)
{
    return floor(x);
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Calculates The Ceiling Of A Value x
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float   mceil(float x)
{
    return ceilf(x);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  mceil(double x)
{
    return ceil(x);
}


///////////////////////////////////////////////////////////////////////////////////////
// Getting Maximum Value 
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
Ttype   mmax(Ttype x, Ttype y)
{
    return (x > y) ? (x) : (y);
}   
///////////////////////////////////////////////////////////////////////////////////////
// Getting Minimum Value 
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
Ttype   mmin(Ttype x, Ttype y)
{
    return (x < y) ? (x) : (y);
}

///////////////////////////////////////////////////////////////////////////////////////
// Sgn
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
M_INLINE Ttype msgn(Ttype x)
{
    return (x > 0) ? (1) : ((x < 0) ? (-1) : (0));
}

///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float msgn(float x)
{
    return (mless0(x)) ? (-1.0f) : ((mgre0(x))?(1.0f):(0.0f));
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double msgn(double x)
{
    return (mless0(x)) ? (-1.0) : ((mgre0(x))?(1.0):(0.0));
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Natural Logarithm (Base e) Of x
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE float   mln(float x)
{
    return logf(x);
}
///////////////////////////////////////////////////////////////////////////////////////
M_INLINE double  mln(double x)
{
    return log(x);
}
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Logarithm Base 10 Of X
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float   mlog10(float x)
{
    return log10f(x);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  mlog10(double x)
{
    return log10(x);
}
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Exponent
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float   mexp(float x)
{
    return expf(x);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  mexp(double x)
{
    return exp(x);
}
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Calculate x Raised To The Power y
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float   mpow(float x, float y)
{
    return powf(x,y);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  mpow(double x, double y)
{
    return pow(x,y);
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Inverting Number 
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float   minvert(float x)
{
    ASSERT(!mnear0(x));
    return 1.0f/x;
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  minvert(double x)
{
    ASSERT(!mnear0(x));
    return 1.0/x;
}


///////////////////////////////////////////////////////////////////////////////////////
// Splits A Floating-Point Value Into Fractional And Integer Parts
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float   mmodf(float x, float *y)
{
    return modff(x,y);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  mmodf(double x, double *y)
{
    return modf(x,y);
}
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Calculates The Floating-Point Remainder
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL float   mfmod(float x, float y)
{
    return fmodf(x,y);
}
///////////////////////////////////////////////////////////////////////////////////////
M_FORCEINL double  mfmodf(double x, double y)
{
    return fmod(x,y);
}
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Packing Values From [-1,1] To [0,1] 
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
M_INLINE TReal mpack01(TReal x)
{
    const TReal half(0.5f);
    return x*half + half;
}

///////////////////////////////////////////////////////////////////////////////////////
// Unpacking Values From [0,1] To [-1,1]
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
M_INLINE TReal munpack01(TReal x)
{
    const TReal two(2);
	const TReal one(1);
	return x*two - one;
}


///////////////////////////////////////////////////////////////////////////////////////
// Smooth Step
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
M_INLINE TReal msmoothstep(TReal x)
{
    return x * x * (T(3) - T(2) * x);
}

///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
M_INLINE TReal mquintic(TReal x)
{
    return x * x * x * (x * (x * T(6) - T(15)) + T(10)); 
}
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
M_INLINE TReal msmoothstepderiv(TReal x)
{
    return x * (T(6) - T(6) * x); 
}
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
M_INLINE TReal mquinticderiv(TReal x)
{
    return T(30) * x * x * (x * (x - T(2)) + T(1));
}


#endif //__ELEMFUNC_INL__
