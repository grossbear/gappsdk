///////////////////////////////////////////////////////////////////////////////////////
//  trigonometry.cpp
//
//  Trigonometry compute functions
//  
//
///////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "base/common/platform/platform_types.h"

#include "mathconsts.h"
#include "mathlibdefs.h"

#include "types/tfixed32.h"
#include "types/tfixed64.h"
#include "types/thalf.h"

#include "elemfunc.h"
#include "trigonometry.h"
#include "intreal.h"


///////////////////////////////////////////////////////////////////////////////////////
// Triginometry Functions
///////////////////////////////////////////////////////////////////////////////////////

#define     TABLESIZE_SIN       256
#define     FIXED_TABLE_SIZE    1024
#define     TWOPISCALE          ((float)TABLESIZE_SIN * ((float)CONST_1_2PI))

const INTFLOAT sinus_tab [TABLESIZE_SIN] = 
{
    #include "tables/sin_table256.h"
};
///////////////////////////////////////////////////////////////////////////////////////
const uint32t fxcos_tab [FIXED_TABLE_SIZE+1] = 
{
    #include "tables/fxcos_table1024.h"
};
///////////////////////////////////////////////////////////////////////////////////////
const uint32t fxsin_tab [FIXED_TABLE_SIZE+1] =
{
    #include "tables/fxsin_table1024.h"
};
///////////////////////////////////////////////////////////////////////////////////////
const uint32t fxtan_tab [FIXED_TABLE_SIZE+1] =
{
    #include "tables/fxtan_table1024.h"
};
///////////////////////////////////////////////////////////////////////////////////////
const uint32t fxacos_tab [FIXED_TABLE_SIZE+1] =
{
    #include "tables/fxacos_table1024.h"
};
///////////////////////////////////////////////////////////////////////////////////////
const ubyte acosdeg_tab [101] = 
{
    #include "tables/acosdeg_table.h"
};
///////////////////////////////////////////////////////////////////////////////////////
static const INTFLOAT bias = {((23 + 127) << 23) + (1 << 22)};

///////////////////////////////////////////////////////////////////////////////////////
// Sinus Function Using Precalculated Table
float m_tsinf(float angle)
{
    ASSERT(angle >= -10000.0f && angle <= 10000.0f);

    INTFLOAT fi;    
    fi.f = angle * TWOPISCALE + bias.f;
    int32t i = fi.i & (TABLESIZE_SIN - 1);
    return sinus_tab[i].f;
}

///////////////////////////////////////////////////////////////////////////////////////
// Cosinus Function Using Precalculated Table
float m_tcosf(float angle)
{
    ASSERT(angle >= -10000.0f && angle <= 10000.0f);

    INTFLOAT  fi;
    fi.f = angle * TWOPISCALE + bias.f;
    int32t i = (fi.i + (TABLESIZE_SIN/4)) & (TABLESIZE_SIN - 1);
    return sinus_tab[i].f;
}

///////////////////////////////////////////////////////////////////////////////////////
// SinCos Function Using Precalculated Table
void m_tsincosf(float angle, float &sin_val, float &cos_val)
{
    ASSERT(angle >= -10000.0f && angle <= 10000.0f);

    INTFLOAT fi;    
    fi.f = angle * TWOPISCALE + bias.f;

    int i = fi.i & (TABLESIZE_SIN - 1);
    sin_val = sinus_tab[i].f;

    i = (fi.i + (TABLESIZE_SIN/4)) & (TABLESIZE_SIN - 1);
    cos_val = sinus_tab[i].f;
}

#ifdef MATH_FIXED_INST
///////////////////////////////////////////////////////////////////////////////////////
// Sinus Function Using Precalculated Table
tfixed32<16> m_tsinx(const tfixed32<16> &x)
{
    static const tfixed32<16> fx2pi = CMathConst< tfixed32<16> >::MATH_2PI;
    
    tfixed32<16> fxval = (*(int32t*)x < 0) ? (fx2pi - x) : (x);
    fxval /= fx2pi;
    fxval &= 0x0000FFFF; //fraction part
    tfixed32<16> fxent;
    *(int32t*)fxent = FIXED_TABLE_SIZE - 1;
    fxval *= fxent;
    
    int32t tabidx = *(int32t*)fxval;
    int32t intval = fxsin_tab[tabidx];
    
    tfixed32<16> outval;
    *(int32t*)outval = intval;
    
    return outval;
}

///////////////////////////////////////////////////////////////////////////////////////
// Cosinus Function Using Precalculated Table
tfixed32<16> m_tcosx(const tfixed32<16> &x)
{
    static const tfixed32<16> fx2pi = CMathConst< tfixed32<16> >::MATH_2PI;
    
    tfixed32<16> fxval = (*(int32t*)x < 0) ? (-x) : (x);
    fxval /= fx2pi;
    fxval &= 0x0000FFFF;
    tfixed32<16> fxent;
    *(int32t*)fxent = FIXED_TABLE_SIZE - 1;
    fxval *= fxent;
    
    int32t tabidx = *(int32t*)fxval;
    int32t intval = fxcos_tab[tabidx];
    
    tfixed32<16> outval;
    *(int32t*)outval = intval;
    
    return outval;
}

///////////////////////////////////////////////////////////////////////////////////////
// Arcus Cosinus Function Using Precalculated Table
tfixed32<16> m_tacosx(const tfixed32<16> &x)
{    
    static const tfixed32<16> one(1);
    
    tfixed32<16> fxval = x + one;
    fxval >>= 1;
    fxval &= 0x0000FFFF;
    tfixed32<16> fxent;
    *(int32t*)fxent = FIXED_TABLE_SIZE - 1;
    fxval *= fxent;
    
    int32t tabidx = *(int32t*)fxval;
    int32t intval = fxacos_tab[tabidx];
    
    tfixed32<16> outval;
    *(int32t*)outval = intval;
    
    return outval;
}

///////////////////////////////////////////////////////////////////////////////////////
// SinCos Function Using Precalculated Table
void m_tsincosx(const tfixed32<16> &angle, tfixed32<16> &sin_val, tfixed32<16> &cos_val)
{    
    static const tfixed32<16> fx2pi = CMathConst< tfixed32<16> >::MATH_2PI;
    
    sin_val = (*(int32t*)angle < 0) ? (fx2pi - angle) : (angle);
    sin_val /= fx2pi;
    sin_val &= 0x0000FFFF;
    
    cos_val = (*(int32t*)angle < 0) ? (-angle) : (angle);
    cos_val /= fx2pi;
    cos_val &= 0x0000FFFF;
    
    tfixed32<16> fxent;
    *(int32t*)fxent = FIXED_TABLE_SIZE - 1;
    
    int32t tabidx = 0;
    int32t intval = 0;
    
    sin_val *= fxent;
    tabidx = *(int32t*)sin_val;
    intval = fxsin_tab[tabidx];
    *(int32t*)sin_val = intval;
    
    cos_val *= fxent;
    tabidx = *(int32t*)cos_val;
    intval = fxcos_tab[tabidx];
    *(int32t*)cos_val = intval;
}
///////////////////////////////////////////////////////////////////////////////////////
#endif //MATH_FIXED_INST

///////////////////////////////////////////////////////////////////////////////////////
// Arcus Cosinus Table Approxiamtion In Degrees
int32t m_tacosdeg(float f)
{
    int32t index = mftoi(f * 100);
    if(index > 100) index = 100;
    ubyte degval = acosdeg_tab[index];
    return (uint32t)degval;
}
///////////////////////////////////////////////////////////////////////////////////////
int32t m_tacosdeg(const tfixed32<16> &x)
{
    static const tfixed32<16> max_idx(100);
    tfixed32<16> fx_index = max_idx * x;
    if( fx_index > max_idx) fx_index = max_idx;
    int32t index = (int32t)fx_index;
    ubyte degval = acosdeg_tab[index];
    return (uint32t)degval;
}
///////////////////////////////////////////////////////////////////////////////////////
