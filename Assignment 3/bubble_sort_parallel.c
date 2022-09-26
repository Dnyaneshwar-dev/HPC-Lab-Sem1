// C Program to find the minimum scalar product of two vectors (dot product)
#include <stdio.h>
#include <time.h>
#include<omp.h>

#define n 100000

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
int sort(int arr[])
{
    int i, j;
    for (i = 0; i < n; i++){
        int turn = i % 2;
        #pragma omp parallel for
        for (j = turn; j < n - 1; j+=2)
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j],&arr[j+1]);
            }
    }
}
int sort_des(int arr[])
{
    int i, j;

    for (i = 0; i < n; ++i)
    {
        int turn = i % 2;
        #pragma omp parallel for 
        for (j = turn; j < n - 1; j += 2)
        {
           //  printf("Thread ID: %d",omp_get_thread_num());
            if (arr[j] < arr[j + 1])
            {
                swap(&arr[j],&arr[j+1]);
            }
        }
    }
}

int main()
{
    omp_set_num_threads(2);

    int arr1[n], arr2[n];
    int i;
    for (i = 0; i < n; i++)

    {
        //scanf("%d", &arr1[i]);
        arr1[i] = n - i;
    }
    for (i = 0; i < n; i++)
    {
        //scanf("%d", &arr2[i]);
        arr2[i] = i;
    }

    double itime, ftime, exec_time;
    itime = omp_get_wtime();
    sort(arr1);
    sort_des(arr2);
    ftime = omp_get_wtime();
    exec_time = ftime - itime;

   
    printf("Time taken (par): %f\n", exec_time);

    int sum = 0;
    for (i = 0; i < n; i++)
    {
        // printf("%d %d\n", arr1[i],arr2[i]);
        sum = sum + (arr1[i] * arr2[i]);
    }
    printf("%d\n", sum);
    return 0;
}