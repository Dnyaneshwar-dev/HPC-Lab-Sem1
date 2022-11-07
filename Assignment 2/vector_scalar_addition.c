#include <omp.h>
#include <stdio.h>
#include <pthread.h>

void main()
{
    int N = 100000;
    int A[N];
    for(int i=0;i<N;i++)A[i] = i + 1;
    int S = 2;

    omp_set_num_threads(6);

    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    #pragma omp parallel for private(S)
    for (int i = 0; i < N; i++)
    {
        A[i] += S;
        // printf("Thread: %d Index: %d\n", omp_get_thread_num(),i);
    }
    ftime = omp_get_wtime();
    exec_time = ftime - itime;

    // for(int i=0;i<N;i++){
    //     printf("%d ", A[i]);
    // }


    
    printf("\nTime taken is %f\n", exec_time);
    printf("\n");
}
// gcc -fopenmp vector_addition.c