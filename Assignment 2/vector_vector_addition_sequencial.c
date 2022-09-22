#include <omp.h>
#include <stdio.h>
#include <pthread.h>

void main()
{
    int N = 100000;
    int A[N];
    for(int i=0;i<N;i++)A[i] = i + 1;

    int B[N];
    for(int i=0;i<N;i++)B[i] = N - i;

    int C[N];
    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    for (int i = 0; i < N; i++)
    {
        C[i] = A[i] + B[i];
        //printf("Thread: %d Index: %d\n", omp_get_thread_num(),i);
    }


    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    // for(int i=0;i<N;i++){
    //     printf("%d ", C[i]);
    // }


    
    printf("\nTime taken is %f\n", exec_time);
    printf("\n");
}
// gcc -fopenmp vector_addition.c