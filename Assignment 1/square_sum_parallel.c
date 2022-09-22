#include <stdio.h>
#include <omp.h>


void main()
{
    long long sum = 0;
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    #pragma omp parallel for reduction( + : sum)
        for (int i = 1; i <= 10000000; i++)
        {
            sum += i * i;
            long long s = i * i;
           // printf("Square of %d = %lld\n",i,s);
        }
    ftime = omp_get_wtime();
    exec_time = ftime - itime;
    printf("\nTime taken is %f\n", exec_time);
    printf("Sum: %lld\n", sum);
}
