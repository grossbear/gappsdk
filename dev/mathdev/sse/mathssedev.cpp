#include <stdio.h>
#include "base/math/mathlib.h"


///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    printf("Math library sse algebra development programme\n");
    
    double factor = 0.5;
    cvec2d vec1(0.0, 0.5);
    cvec2d vec2(1.0, 1.0);
    cvec2d vout(0,0);
    mvec2lrp(vout, vec1, vec2, factor);

    printf("lerp vector: x = %f, y = %f\n", vout.x, vout.y);

    return 0;
}
