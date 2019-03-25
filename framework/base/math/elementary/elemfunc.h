///////////////////////////////////////////////////////////////////////////////////////
//  elemfunc.h
//
//  Math elementary functions header file
//
///////////////////////////////////////////////////////////////////////////////////////

#ifndef __ELEMFUNC_H__
#define __ELEMFUNC_H__

///////////////////////////////////////////////////////////////////////////////////////
// Converting Functions From Integer To Float Type And Vice Versa
///////////////////////////////////////////////////////////////////////////////////////
M_API float     mitof(int32t i);
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    mftoi(float f);

///////////////////////////////////////////////////////////////////////////////////////
// Converting Functions From Integer To Double Type And Vice Versa
///////////////////////////////////////////////////////////////////////////////////////
M_API double    mitod(int64t i);
///////////////////////////////////////////////////////////////////////////////////////
M_API int64t    mdtoi(double d);

///////////////////////////////////////////////////////////////////////////////////////
// Converting Data Types Functions
///////////////////////////////////////////////////////////////////////////////////////
float mtoreal(int32t i);
///////////////////////////////////////////////////////////////////////////////////////
int32t mtoint(float f);
///////////////////////////////////////////////////////////////////////////////////////

double mtoreal(int64t i);
///////////////////////////////////////////////////////////////////////////////////////
int64t mtoint(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Making Float Number
M_API float     mmakef(int32t sign, int32t exp, int32t mantissa);
///////////////////////////////////////////////////////////////////////////////////////
// Splitting Float Number
M_API void      msplitf(float f, int32t &sign, int32t &exp, int32t &mant);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Making Double Number
M_API double    mmaked(int64t sign, int64t exp, int64t mantissa);
///////////////////////////////////////////////////////////////////////////////////////
// Splitting Double Number
M_API void      msplitd(double d, int64t &sign, int64t &exp, int64t &mant);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Lomont Compare Function
// Fast Function To Compare Two Floating Point Numbers
M_API bool mlcmp(float af, float bf, int32t maxDiff);

///////////////////////////////////////////////////////////////////////////////////////
// Checking If Value Is Not A Number
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    misnan(float f);
M_API int64t    misnan(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Signaling NaN
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    msnan(float f);
M_API int64t    msnan(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Quiet NaN
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    mqnan(float f);
M_API int64t    mqnan(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Infinity
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    misinf(float f);
M_API int64t    misinf(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Positive Infinity
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    mpinf(float f);
M_API int64t    mpinf(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Negative Infinity
///////////////////////////////////////////////////////////////////////////////////////
M_API int32t    mninf(float f);
M_API int64t    mninf(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Is Near Zero Value
///////////////////////////////////////////////////////////////////////////////////////
bool  mnear0(float f);
bool  mnear0(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Absolute Value Functions
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
Ttype   mabs(Ttype i);
///////////////////////////////////////////////////////////////////////////////////////
float   mabs(float f);
double  mabs(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Negate Values
///////////////////////////////////////////////////////////////////////////////////////
float   mnegate(float f);
double  mnegate(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Greater Than 0
/////////////////////////////////////////////////////////////////////////////////////// 
bool  mgre0(float f);
bool  mgre0(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Greater Or Equals Zero
///////////////////////////////////////////////////////////////////////////////////////
bool  mgreq0(float f);
bool  mgreq0(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Equals Zero
///////////////////////////////////////////////////////////////////////////////////////
bool    mis0(float f);
bool    mis0(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Less Or Equals Zero
///////////////////////////////////////////////////////////////////////////////////////
bool mlesseq0(float f);
bool mlesseq0(double d);
///////////////////////////////////////////////////////////////////////////////////////
#define mlse0 mlesseq0

///////////////////////////////////////////////////////////////////////////////////////
// Check If Value Is Less Than 0
///////////////////////////////////////////////////////////////////////////////////////
bool  mless0(float f);
bool  mless0(double d);
///////////////////////////////////////////////////////////////////////////////////////
#define mls0 mless0

///////////////////////////////////////////////////////////////////////////////////////
// Clamp Float Value To 0
///////////////////////////////////////////////////////////////////////////////////////
float   mclamp0(float f);
double  mclamp0(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Clamp Value To 1
///////////////////////////////////////////////////////////////////////////////////////
float   mclamp1(float f);
double  mclamp1(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Clamp Value To [0,1]
///////////////////////////////////////////////////////////////////////////////////////
float   mclamp01(float f);
///////////////////////////////////////////////////////////////////////////////////////
double  mclamp01(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Clamp Value To [0, inf)
///////////////////////////////////////////////////////////////////////////////////////
M_API float   mclampnneg(float f);
///////////////////////////////////////////////////////////////////////////////////////
M_API double  mclampnneg(double d);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Function Template Clamping Value
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
Ttype   mclamp(const Ttype &min, const Ttype &max, const Ttype &i);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Number Is Power Of 2
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
bool mispow2(Ttype n);
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Higher Power Of 2
///////////////////////////////////////////////////////////////////////////////////////
int8t       mhpow2(int8t n);
uint8t      mhpow2(uint8t n);
int16t      mhpow2(int16t n);
uint16t     mhpow2(uint16t n);
int32t      mhpow2(int32t n);
uint32t     mhpow2(uint32t n);
int64t      mhpow2(int64t n);
uint64t     mhpow2(uint64t n);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Lower Power Of 2
///////////////////////////////////////////////////////////////////////////////////////
int8t       mlpow2(int8t n);
uint8t      mlpow2(uint8t n);
int16t      mlpow2(int16t n);
uint16t     mlpow2(uint16t n);
int32t      mlpow2(int32t n);
uint32t     mlpow2(uint32t n);
int64t      mlpow2(int64t n);
uint64t     mlpow2(uint64t n);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Check If Number Is A Primary Number
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
bool misprim(Ttype n);
///////////////////////////////////////////////////////////////////////////////////////
//template bool misprim<uint8t>(uint8t n);
///////////////////////////////////////////////////////////////////////////////////////
//template bool misprim<uint16t>(uint16t n);
///////////////////////////////////////////////////////////////////////////////////////
//template bool misprim<uint32t>(uint32t n);
///////////////////////////////////////////////////////////////////////////////////////
//template bool misprim<uint64t>(uint64t n);
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Packing Values From [-1,1] To [0,1]
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
TReal   mpack01(TReal x);
///////////////////////////////////////////////////////////////////////////////////////
void    mpack01(float out[], const float in[], int32t size);
///////////////////////////////////////////////////////////////////////////////////////
void    mpack01(float &xout, float &yout, float &zout, float xin, float yin, float zin);
///////////////////////////////////////////////////////////////////////////////////////
void    mpack01_3(float out[], const float in[]);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Unpacking Values From [0,1] To [-1,1]
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
TReal   munpack01(TReal x);
///////////////////////////////////////////////////////////////////////////////////////
void    munpack01(float out[], const float in[], int32t size);
///////////////////////////////////////////////////////////////////////////////////////
void    munpack01(float &xout, float &yout, float &zout, float xin, float yin, float zin);
///////////////////////////////////////////////////////////////////////////////////////
void    munpack01_3(float out[], const float in[]);
///////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////
// Calculates The Floor Of A Value x
///////////////////////////////////////////////////////////////////////////////////////
float   mfloor(float x);
double  mfloor(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Calculates The Ceiling Of A Value x
///////////////////////////////////////////////////////////////////////////////////////
float   mceil(float x);
double  mceil(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Finds Fraction Part Of Number x
///////////////////////////////////////////////////////////////////////////////////////
float   mfrc(float x);
double  mfrc(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Normalizing Angle To [-PI,PI]
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
TReal   mnorma(TReal rad);
///////////////////////////////////////////////////////////////////////////////////////
//float mnorma(float rad)
///////////////////////////////////////////////////////////////////////////////////////
//double mnorma(double rad)
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Set To Zero If Value Is Nearly Zero
///////////////////////////////////////////////////////////////////////////////////////
float   malign0(float x);
double  malign0(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Set To One If Value Is Nearly One
///////////////////////////////////////////////////////////////////////////////////////
float   malign1(float x);
double  malign1(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Getting Maximum Value 
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
Ttype   mmax(Ttype x, Ttype y);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Getting Minimum Value 
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
Ttype   mmin(Ttype x, Ttype y);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Sgn
///////////////////////////////////////////////////////////////////////////////////////
template <typename Ttype>
Ttype   msgn(Ttype x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Natural Logarithm (Base e) Of x
///////////////////////////////////////////////////////////////////////////////////////
float   mln(float x);
double  mln(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Logarithm Base 10 Of X
///////////////////////////////////////////////////////////////////////////////////////
float   mlog10(float x);
double  mlog10(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Exponent
///////////////////////////////////////////////////////////////////////////////////////
float   mexp(float x);
double  mexp(double x);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Calculate x Raised To The Power y
///////////////////////////////////////////////////////////////////////////////////////
float   mpow(float x, float y);
double  mpow(double x, double y);
///////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// Inverting Number 
///////////////////////////////////////////////////////////////////////////////////////
float   minvert(float x);
double  minvert(double x);
#define minv minvert

///////////////////////////////////////////////////////////////////////////////////////
// Splits A Floating-Point Value Into Fractional And Integer Parts
///////////////////////////////////////////////////////////////////////////////////////
float   mmodf(float x, float *y);
double  mmodf(double x, double *y);

///////////////////////////////////////////////////////////////////////////////////////
// Calculates The Floating-Point Remainder
///////////////////////////////////////////////////////////////////////////////////////
float   mfmod(float x, float y);
double  mfmodf(double x, double y);


#include "elemfunc.inl"

#endif //__ELEMFUNC_H__
