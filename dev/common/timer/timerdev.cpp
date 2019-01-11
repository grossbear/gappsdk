#include <stdio.h>
#include <cmath>
#include "base/common/timer/stopwatch.h"

int main()
{
    printf("timer dev programme\n");

    CStopWatch timer(true);
    
    for(int i = 0; i < 100; i++)
    {
        double angle = sin((double)i);
        angle *= (double)i;
    }

    //float angle = sinf(3.14159f);

    timer.Stop();

    double deltatime = timer.GetTime();
    printf("delta time = %.9f\n",deltatime);

    unsigned int tickscnt = timer.GetTicks();
    printf("ticks count = %u\n",tickscnt);

    return 0;
}
