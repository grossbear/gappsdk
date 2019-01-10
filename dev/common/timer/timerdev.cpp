#include <stdio.h>
#include <cmath>
#include "base/common/timer/stopwatch.h"

int main()
{
    printf("timer dev programme\n");

    CHighResStopWatch timer(true);
    
    for(int i = 0; i < 100000; i++)
    {
        double angle = sin((double)i);
        angle *= (double)i;
    }

    //double angle = sin(3.14159);

    timer.Stop();

    float deltatime = timer.GetTime();
    printf("delta time = %f\n",deltatime);

    unsigned int tickscnt = timer.GetTicks();
    printf("ticks count = %u\n",tickscnt);

    return 0;
}
