///////////////////////////////////////////////////////////////////////////////////////
//  thalf.cpp
//
//  Half precision floating point class and conversion functions
//  
//
///////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "base/common/platform_types.h"

#include "mathconsts.h"
#include "mathlibdefs.h"

#include "thalf.h"

#ifdef MATH_ILM_HALF_CONVERSION
///////////////////////////////////////////////////////////////////////////////////////
// Float To Half Conversion
// Including Zeros, Denormalized Numbers And Exponent Overflows
uint16t mftoh(float f)
{
    ///////////////////////////////////////////////////////////////////////////////////////
    // Our floating point number, f, is represented by the bit
    // pattern in integer i.  Disassemble that bit pattern into
    // the sign, s, the exponent, e, and the significand, m.
    // Shift s into the position where it will go in in the
    // resulting half number.
    // Adjust e, accounting for the different exponent bias
    // of float and half (127 versus 15).
    ///////////////////////////////////////////////////////////////////////////////////////

    int32t i = *(int32t*)&f;

    register int32t  s =  (i >> 16)  & 0x00008000;
    register int32t  e =  ((i >> 23) & 0x000000ff) - (127 - 15);
    register int32t  m =   i         & 0x007fffff;

    
    // Now reassemble s, e and m into a half:
    if (e <= 0)
    {
	    if (e < -10)
        {
	        ///////////////////////////////////////////////////////////////////////////////////////
	        // E is less than -10.  The absolute value of f is
	        // less than HALF_MIN (f may be a small normalized
	        // float, a denormalized float or a zero).
	        //
	        // We convert f to a half zero with the same sign as f.
	        ///////////////////////////////////////////////////////////////////////////////////////

	        return s;
	    }

	    ///////////////////////////////////////////////////////////////////////////////////////
	    // E is between -10 and 0.  F is a normalized float
	    // whose magnitude is less than HALF_NRM_MIN.
	    //
	    // We convert f to a denormalized half.
	    /////////////////////////////////////////////////////////////////////////////////////// 

	    m = (m | 0x00800000) >> (1 - e);

	    ///////////////////////////////////////////////////////////////////////////////////////
	    // Round to nearest, round "0.5" up.
	    //
	    // Rounding may cause the significand to overflow and make
	    // our number normalized.  Because of the way a half's bits
	    // are laid out, we don't have to treat this case separately;
	    // the code below will handle it correctly.
	    /////////////////////////////////////////////////////////////////////////////////////// 

	    if (m &  0x00001000)
	        m += 0x00002000;

	    ///////////////////////////////////////////////////////////////////////////////////////
	    // Assemble the half from s, e (zero) and m.
	    ///////////////////////////////////////////////////////////////////////////////////////

	    return s | (m >> 13);
    }
    else if (e == 0xff - (127 - 15))
    {
	    if (m == 0)
	    {
	        ///////////////////////////////////////////////////////////////////////////////////////
	        // F is an infinity; convert f to a half
	        // infinity with the same sign as f.
	        ///////////////////////////////////////////////////////////////////////////////////////

	        return s | 0x7c00;
	    }
	    else
	    {
	        ///////////////////////////////////////////////////////////////////////////////////////
	        // F is a NAN; we produce a half NAN that preserves
	        // the sign bit and the 10 leftmost bits of the
	        // significand of f, with one exception: If the 10
	        // leftmost bits are all zero, the NAN would turn 
	        // into an infinity, so we have to set at least one
	        // bit in the significand.
	        ///////////////////////////////////////////////////////////////////////////////////////

	        m >>= 13;
	        return s | 0x7c00 | m | (m == 0);
	    }
    }
    else
    {
	    ///////////////////////////////////////////////////////////////////////////////////////
	    // E is greater than zero.  F is a normalized float.
	    // We try to convert f to a normalized half.
	    ///////////////////////////////////////////////////////////////////////////////////////

	    ///////////////////////////////////////////////////////////////////////////////////////
	    // Round to nearest, round "0.5" up
	    ///////////////////////////////////////////////////////////////////////////////////////

	    if (m &  0x00001000)
	    {
	        m += 0x00002000;

	        if (m & 0x00800000)
	        {
		        m =  0;		// overflow in significand,
		        e += 1;		// adjust exponent
	        }
	    }

	    ///////////////////////////////////////////////////////////////////////////////////////
	    // Handle exponent overflow
	    ///////////////////////////////////////////////////////////////////////////////////////

	    if (e > 30)
	    {
	        //--overflow ();	    // Cause a hardware floating point overflow;

	        return s | 0x7c00;	// if this returns, the half becomes an
	    }   			        // infinity with the same sign as f.

	    ///////////////////////////////////////////////////////////////////////////////////////
	    // Assemble the half from s, e and m.
	    ///////////////////////////////////////////////////////////////////////////////////////

	    return s | (e << 10) | (m >> 13);
    }
}
#else //Conversion Function From ATI SDK
///////////////////////////////////////////////////////////////////////////////////////
uint16t mftoh(float f)
{
    uint32t x = *(uint32t *)&f;
    uint32t sign = (uint16t)(x >> 31);
    uint32t mantissa;
    int32t exp;
    uint16t half;

    //Get Mantissa
    mantissa = x & ((1 << 23) - 1);

    //Get Exponent Bits
    exp =  (int32t)((x >> 23) & 0xFF) - 127;

    if (exp > 16)
    {
        // Largest Possible Half Float Number
        exp = 16;
        mantissa = (1 << 23) - 1;   
    }
    else if (exp <= -15)
    {
        // All Float Denorm And 0 Values Map To Half 0
        mantissa = 0;
        exp = -15;
    }

    half = (((uint16t)sign) << 15 )  | (((uint16t)(exp + 15 )) << 10) | (uint16t)(mantissa >> 13);

    return half;
}
#endif //MATH_ILM_HALF_CONVERSION

#ifdef MATH_ILM_HALF_CONVERSION
///////////////////////////////////////////////////////////////////////////////////////
// Converting Half Value To Float Value
float mhtof(uint16t h)
{
    int32t s = (h >> 15) & 0x00000001;
    int32t e = (h >> 10) & 0x0000001f;
    int32t m =  h        & 0x000003ff;

    if (e == 0)
    {
	    if (m == 0)
	    {
	        // Plus or minus zero
            s = s << 31;
	        return *(float*)&s; //(s << 31)
	    }
	    else
	    {
	        // Denormalized number -- renormalize it
	        while (!(m & 0x00000400))
	        {
		        m <<= 1;
		        e -=  1;
	        }

	        e += 1;
	        m &= ~0x00000400;
	    }
    }
    else if (e == 31)
    {
	    if (m == 0)
	    {
	        // Positive or negative infinity
            s = ((s << 31) | 0x7f800000);
	        return *(float*)&s; //((s << 31) | 0x7f800000)
	    }
	    else
	    {
	        // Nan -- preserve sign and significand bits
            s = ((s << 31) | 0x7f800000 | (m << 13));
	        return *(float*)&s;
	    }
    }

    // Normalized number
    e = e + (127 - 15);
    m = m << 13;

    // Assemble s, e and m.
    int32t i = (s << 31) | (e << 23) | m;
    float f = *(float*)&i;

    return f;
}
#else
///////////////////////////////////////////////////////////////////////////////////////
float mhtof(uint16t h)
{
    uint32t sign = (uint32t)(h >> 15);
    uint32t mantissa = (uint32t)(h & ((1 << 10) - 1));
    int32t  exp = (int32t)((h >> 10) & 0x1F) - 15;
    uint32t f;

    if (exp == 16)
    {
        // Convert 16-bit FP inf/NaN To 32-bit inf/NaN Value
        exp = 128;
    }
    else if (exp == -15)
    {
        // Convert 16-bit FP zero/denorm To 32-bit zero/denorm Value
        exp = -127;
    }
    f = (sign << 31) | ((exp + 127) << 23) | (mantissa << 13);

    return *(float *)&f;
}
#endif //MATH_ILM_HALF_CONVERSION


///////////////////////////////////////////////////////////////////////////////////////
// Making Half Number
M_API uint16t   mmakeh(int32t sign, int32t exp, int32t mant)
{   
    uint16t half = (sign << 15) | ((exp & 31) << 10) | (mant & ((1 << 10) - 1));

    return half;
}
///////////////////////////////////////////////////////////////////////////////////////
// Splitting Half Number
M_API void      msplith(uint16t h, int32t &sign, int32t &exp, int32t &mant)
{
    sign = (h >> 15) != 0 ? 1 : 0;
    exp =  (h >> 10) & 31;
    mant = h & ((1 << 10) - 1);
}

///////////////////////////////////////////////////////////////////////////////////////
// Testing Value Functions
///////////////////////////////////////////////////////////////////////////////////////
// Test If Not A Number
bool misnan(uint16t h)
{
    int32t s,e,m;
    msplith(h,s,e,m);

    return (e == 255) && (m != 0);
}
///////////////////////////////////////////////////////////////////////////////////////
// If Quiet NaN
bool mqnan(uint16t h)
{
    int32t s,e,m;
    msplith(h,s,e,m);

    return (e == 255) && (m != 0) && !(m >> 9);
}
///////////////////////////////////////////////////////////////////////////////////////
// If Signaling NaN
bool msnan(uint16t h)
{
    int32t s,e,m;
    msplith(h,s,e,m);

    return (e == 255) && (m != 0) && (m >> 9);
}

///////////////////////////////////////////////////////////////////////////////////////
// Is Infinity
bool misinf(uint16t h)
{
    int32t s,e,m;
    msplith(h,s,e,m);

    return (e == 31) && (m == 0);
}
///////////////////////////////////////////////////////////////////////////////////////
// Is Positive Infinity
bool mpinf(uint16t h)
{
    int32t s,e,m;
    msplith(h,s,e,m);

    return (s == 0) && (e == 31) && (m == 0);
}
///////////////////////////////////////////////////////////////////////////////////////
// Is Negative Infinity
bool mninf(uint16t h)
{
    int32t s,e,m;
    msplith(h,s,e,m);

    return (s == 1) && (e == 31) && (m == 0);
}

///////////////////////////////////////////////////////////////////////////////////////
// Math 16-bit half precision floating point type class
///////////////////////////////////////////////////////////////////////////////////////
// Class Constructors
///////////////////////////////////////////////////////////////////////////////////////
thalf::thalf():value(0){}
///////////////////////////////////////////////////////////////////////////////////////
thalf::thalf(const thalf &half_val):value(half_val.value){}
///////////////////////////////////////////////////////////////////////////////////////
thalf::thalf(float f_val)
{
    value = mftoh(f_val);
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::thalf(double d_val)
{
    value = mftoh((float)d_val);
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::thalf(int32t i_val)
{
    value = mftoh((float)i_val);
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::thalf(int16t i_val)
{
    value = mftoh((float)i_val);
}

///////////////////////////////////////////////////////////////////////////////////////
// Cast To Pointer uint16t *
thalf::operator uint16t* () const
{
    return (uint16t*) this;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::operator const uint16t* () const
{
    return (const uint16t*) this;
}

///////////////////////////////////////////////////////////////////////////////////////
// Cast To Promitive Built-in Types
thalf::operator float() const
{
    return mhtof(value);
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::operator double() const
{
    return (double)mhtof(value);
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::operator int32t() const
{
    return (int32t)mhtof(value);
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::operator int16t() const
{
    return (int16t)mhtof(value);
}
///////////////////////////////////////////////////////////////////////////////////////
thalf::operator bool() const
{
    return value != 0;
}


///////////////////////////////////////////////////////////////////////////////////////
// Assignment Operators
thalf& thalf::operator = (const thalf& half_val)
{
    value = half_val.value;
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf& thalf::operator +=(const thalf& half_val)
{
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    value = mftoh(lvalue + rvalue);
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf& thalf::operator -=(const thalf& half_val)
{
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    value = mftoh(lvalue - rvalue);
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf& thalf::operator *=(const thalf& half_val)
{
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    value = mftoh(lvalue * rvalue);
    return *this;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf& thalf::operator /=(const thalf& half_val)
{
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    value = mftoh(lvalue / rvalue);
    return *this;
}

///////////////////////////////////////////////////////////////////////////////////////
// Unary Operators
thalf thalf::operator + () const
{
    thalf out;
    out.value = value;
    return out;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf thalf::operator - () const
{
    thalf out;
    out.value = value;
    return out;
}

///////////////////////////////////////////////////////////////////////////////////////
// Binary Operators
thalf thalf::operator + (const thalf &half_val) const
{
    thalf out;
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    out.value = mftoh(lvalue + rvalue);
    return out;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf thalf::operator - (const thalf &half_val) const
{
    thalf out;
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    out.value = mftoh(lvalue - rvalue);
    return out;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf thalf::operator * (const thalf &half_val) const
{
    thalf out;
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    out.value = mftoh(lvalue * rvalue);
    return out;
}
///////////////////////////////////////////////////////////////////////////////////////
thalf thalf::operator / (const thalf &half_val) const
{
    thalf out;
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    out.value = mftoh(lvalue / rvalue);
    return out;
}
///////////////////////////////////////////////////////////////////////////////////////
bool thalf::operator == (const thalf &half_val) const
{
    return value == half_val.value;
}
///////////////////////////////////////////////////////////////////////////////////////
bool thalf::operator != (const thalf &half_val) const
{
    return value != half_val.value;
}
///////////////////////////////////////////////////////////////////////////////////////
bool thalf::operator <  (const thalf &half_val) const
{
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    return lvalue < rvalue;
}
///////////////////////////////////////////////////////////////////////////////////////
bool thalf::operator >  (const thalf &half_val) const
{
    float lvalue = (float)*this;
    float rvalue = (float)half_val;
    return lvalue > rvalue;
}

///////////////////////////////////////////////////////////////////////////////////////
bool thalf::operator <= (const thalf &half_val) const
{
    return (value == half_val.value) ? (true) : (((float)*this) < ((float)half_val));
}
///////////////////////////////////////////////////////////////////////////////////////
bool thalf::operator >= (const thalf &half_val) const
{
    return (value == half_val.value) ? (true) : (((float)*this) > ((float)half_val));
}

///////////////////////////////////////////////////////////////////////////////////////
