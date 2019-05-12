#include <stdio.h>
#include "base/math/mathlib.h"


///////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    printf("Math library sse algebra development programme\n");
    
    cvec2f vec1(-0.25f, 0.5f);
    cvec2f vec2 = vec1 + cvec2f(0.2f, 0.2f);

    return 0;
}
