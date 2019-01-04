#include <stdio.h>
#include <cmath>
#include "base/common/timer/timer.h"

int main()
{
    printf("timer dev programme\n");

    CStopWatch timer(true);
    for(int i = 0; i < 1000; i++)
    {
        double angle = sin((double)i);
    }

    float deltatime = timer.GetTime();
    printf("delta time = %f\n",deltatime);

    return 0;
}
