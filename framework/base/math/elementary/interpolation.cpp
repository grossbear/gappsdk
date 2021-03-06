///////////////////////////////////////////////////////////////////////////////////////
//  interpolations.h
//
//  Interpolation functions definitions
//
///////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

#include "base/common/platform/platform_types.h"
    
#include "mathconsts.h"
#include "mathlibdefs.h"

#include "types/tfixed32.h"
#include "types/tfixed64.h"
#include "types/thalf.h"

#include "trigonometry.h"
#include "interpolation.h"


///////////////////////////////////////////////////////////////////////////////////////
// Cosinus interpolation between two values
///////////////////////////////////////////////////////////////////////////////////////
template <typename TReal>
TReal   mcosrp(TReal v1, TReal v2, TReal factor)
{
    static const TReal one = TReal(1.0);
    static const TReal half = TReal(0.5);
    
    TReal angle = factor * CMathConst<TReal>::MATH_PI;
    TReal prc = (one - mcos(angle))*half;
    
    TReal outval = mlerp(v1,v2,prc);
    
    return outval;
}
///////////////////////////////////////////////////////////////////////////////////////
// Instantiation of Function mcosrp
template float mcosrp<float>(float v1, float v2, float factor);
///////////////////////////////////////////////////////////////////////////////////////
template double mcosrp<double>(double v1, double v2, double factor);
///////////////////////////////////////////////////////////////////////////////////////