///////////////////////////////////////////////////////////////////////////////////////
// Prng.cpp
//
// Pseudo random number generation functions.
// Generates values in range -1,1.
//
///////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "base/common/platform/platform_types.h"
#include "mathconsts.h"
#include "mathlibdefs.h"
#include "elementary/elemfunc.h"
#include "elementary/interpolation.h"
#include "prng.h"

///////////////////////////////////////////////////////////////////////////////////////
// Pseudo random number generation function
// Returns values from 0 to 32767
unsigned int mprng()
{
    // Our initial starting seed is 5323
    static unsigned int nseed = 5323;

    // Take the current seed and generate a new value from it
    // due to our use of large constants and overflow, it would be
    // very hard for someone to predict what the next number is
    // going to be from the previous one.
    nseed = (8253729 * nseed + 2396403);
 
    // Take the seed and return a value between 0 and 32767
    return nseed % 32767;
}

///////////////////////////////////////////////////////////////////////////////////////
// Pseudo random number generation function
float mprng(int32t x)
{
    int32t n = (x << 13) ^ x;
    
    return (1.0f - ((n*(n*n*15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

///////////////////////////////////////////////////////////////////////////////////////
// Pseudo random number generation function
float mprng(int32t x, int32t y)
{
    int32t n = x + y * 57;
    n = (n << 13) ^ n;
    
    return (1.0f - ((n*(n*n*15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

///////////////////////////////////////////////////////////////////////////////////////
// Pseudo random number generation function
float mprng(int32t x, int32t y, int32t z)
{
    int32t n = x + y * 57 + z * 131;
    n = (n << 13) ^ n;
    
    return (1.0f - ((n*(n*n*15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

///////////////////////////////////////////////////////////////////////////////////////
// Pseudo random number generation function
float mprng(int32t x, int32t y, int32t z, int32t w)
{
    int32t n = x + y * 57 + z * 131 + w * 323;
	n = (n << 13) ^ n;

	return (1.0f - ((n*(n*n*15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

///////////////////////////////////////////////////////////////////////////////////////
// Mixed pseudo random number generation function
float mmixprng(int32t x)
{
    return mprng(x)/2.f + mprng(x-1)/4.f + mprng(x+1)/4.f;
}

///////////////////////////////////////////////////////////////////////////////////////
// Mixed pseudo random number generation function
float mmixprng(int32t x, int32t y)
{
	float corners = (mprng(x-1,y-1) + mprng(x+1,y-1) + mprng(x-1,y+1) + mprng(x+1,y+1))/16.f;
	float sides = (mprng(x+1,y) + mprng(x-1,y) + mprng(x,y+1) + mprng(x,y-1))/8.f;
	float center = mprng(x,y)/4.f;

	return corners + sides + center;    
}

///////////////////////////////////////////////////////////////////////////////////////
// Mixed pseudo random number generation function
float mmixprng2d(int32t x, int32t y, int32t z)
{
    float corners = (mprng(x-1,y-1,z) + mprng(x+1,y-1,z) + mprng(x-1,y+1,z) + mprng(x+1,y+1,z))/16.f;
	float sides = (mprng(x+1,y,z) + mprng(x-1,y,z) + mprng(x,y+1,z) + mprng(x,y-1,z))/8.f;
	float center = mprng(x,y,z)/4.f;

	return corners + sides + center;
}

///////////////////////////////////////////////////////////////////////////////////////
// Mixed pseudo random number generation function
float mmixprng(int32t x, int32t y, int32t z)
{
	float corners = (mprng(x-1,y-1,z+1) + mprng(x+1,y-1,z+1) + mprng(x-1,y+1,z+1) +
						mprng(x+1,y+1,z+1) + mprng(x+1,y,z+1) + mprng(x-1,y,z+1) +
						mprng(x,y+1,z+1) + mprng(x,y-1,z+1) +
					mprng(x-1,y-1,z) + mprng(x+1,y-1,z) + mprng(x-1,y+1,z) +
						mprng(x+1,y+1,z) +
					mprng(x-1,y-1,z-1) + mprng(x+1,y-1,z-1) + mprng(x-1,y+1,z-1) +
						mprng(x+1,y+1,z-1) + mprng(x+1,y,z-1) + mprng(x-1,y,z-1) +
						mprng(x,y+1,z-1) + mprng(x,y-1,z-1)
						)/32.f;

	float sides = (mprng(x,y,z+1) + mprng(x+1,y,z) + mprng(x-1,y,z) +
					mprng(x,y+1,z) + mprng(x,y-1,z) + mprng(x,y,z-1))/24.f;

	float center = mprng(x,y,z)/8.f;
	
	return corners + sides + center;    
}

///////////////////////////////////////////////////////////////////////////////////////
// Smooth pseudo random value generation 
float msmprng(float x)
{
    int32t xinteger = mtoint(x);
	float fractionx = x - float(xinteger);
	float v1,v2;
	
	v1 = mmixprng(xinteger);
	v2 = mmixprng(xinteger+1);

	return mcosrp(v1,v2,fractionx);
}

///////////////////////////////////////////////////////////////////////////////////////
// Smooth pseudo random value generation 
float msmprng(float x, float y)
{
    int32t xinterger = mtoint(x);
    float fractionx = x - mtoreal(xinterger);
    int32t yinteger = mtoint(y);
    float fractiony = y - mtoreal(yinteger);
    float v1,v2,v3,v4,i1,i2;
    float ret;

    v1 = msmprng(xinterger, yinteger);
    v2 = msmprng(xinterger + 1, yinteger);
    v3 = msmprng(xinterger, yinteger + 1);
    v4 = msmprng(xinterger + 1, yinteger + 1);
    i1 = mcosrp (v1,v2,fractionx);
    i2 = mcosrp (v3,v4,fractionx);
    ret = mcosrp (i1,i2,fractiony);

    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////
// Smooth pseudo random value generation
float msmprng(float x, float y, float z, bool smooth2d)
{
    int32t xinterger = mtoint(x);
    float fractionx = x - mtoreal(xinterger);
    int32t yinteger = mtoint(y);
    float fractiony = y - mtoreal(yinteger);
    int32t zinteger = mtoint(z);
    float fractionz = z - mtoreal(zinteger);
    float v1,v2,v3,v4,v5,v6,v7,v8, i1,i2,ires1, i3,i4,ires2;
    float ret;

    float (*fpfun)(int32t,int32t,int32t);
    if(smooth2d)
        fpfun = mmixprng2d; //3d
    else
        fpfun = mmixprng; //3d

    v1 = fpfun(xinterger, yinteger, zinteger);
    v2 = fpfun(xinterger + 1, yinteger, zinteger);
    v3 = fpfun(xinterger, yinteger + 1, zinteger);
    v4 = fpfun(xinterger + 1, yinteger + 1, zinteger);

    v5 = fpfun(xinterger, yinteger, zinteger + 1);
    v6 = fpfun(xinterger + 1, yinteger, zinteger + 1);
    v7 = fpfun(xinterger, yinteger + 1, zinteger + 1);
    v8 = fpfun(xinterger + 1, yinteger + 1, zinteger + 1);

    i1 = mcosrp (v1,v2,fractionx);
    i2 = mcosrp (v3,v4,fractionx);
    ires1 = mcosrp (i1,i2,fractiony);

    i3 = mcosrp (v5,v6,fractionx);
    i4 = mcosrp (v7,v8,fractionx);
    ires2 = mcosrp (i3,i4,fractiony);

    ret = mcosrp (ires1,ires2,fractionz);

    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////
// Functions from Game Programming Gems book

///////////////////////////////////////////////////////////////////////////////////////
// Fractal Brownian Motion
// FBM Fractal in 2d 
float mfbm(float x, float y, int octaves, float amplitude, float frequence, float h)
{
    float ret = 0.0f;
    for(int i=0; i<octaves; i++)
    {
        ret += msmprng(x*frequence, y*frequence)*amplitude;
        amplitude *= h;
        //frequence /= h;
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////
// Fractal Brownian Motion
// FBM fractal in 3d
float mfbm(float x, float y, float z, int32t octaves, float amplitude, float frequence, 
		  float h, bool smooth2d)
{
    float ret = 0.0f;
    for(int32t i=0; i<octaves; i++)
    {
        ret += msmprng(x*frequence, y*frequence, z*frequence, smooth2d)*amplitude;
        amplitude *= h;
        //frequence /= h;
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////
// Multifractal in 2d
float mmultifractal(float x, float y, int32t octaves, float amplitude, float frequence, float h,
				   float offset)
{
    float ret = 1.f;
    for(int32t i=0; i<octaves; i++)
    {
        ret *= offset*(msmprng(x*frequence,y*frequence)*amplitude);
        amplitude *= h;
    }

    return ret;
}

///////////////////////////////////////////////////////////////////////////////////////
// Multifractal in 3d
float mmultifractal(float x, float y, float z, int32t octaves, float amplitude, float frequence,
				   float h, float offset, bool smooth2d)
{
    float ret = 1.f;
    for(int32t i=0; i<octaves; i++)
    {
        ret *= offset*(msmprng(x*frequence,y*frequence,z*frequence,smooth2d)*amplitude);
        amplitude *= h;
    }

    return ret;
}
