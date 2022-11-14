#include<stdio.h>


__global__ void scan(float *g_odata, float *g_idata, int n)
{
 extern __shared__ float temp[]; // allocated on invocation
 int thid = threadIdx.x;
 int pout = 0, pin = 1;
 // load input into shared memory.
 // This is exclusive scan, so shift right by one and set first elt to 0
 temp[pout*n + thid] = (thid > 0) ? g_idata[thid-1] : 0;
 __syncthreads();
 for (int offset = 1; offset < n; offset *= 2)
 {
 pout = 1 - pout; // swap double buffer indices
 pin = 1 - pout;
 if (thid >= offset)
 temp[pout*n+thid] += temp[pin*n+thid - offset];
 else
 temp[pout*n+thid] = temp[pin*n+thid];
 __syncthreads();
 }
 g_odata[thid] = temp[pout*n+thid1]; // write output
} 



void initWith(float val, float *arr, int N)
{
  for (int i = 0; i < N; i++)
  {
    arr[i] = val;
  }
}

void checkRes(float *arr, float *res, int N, float *ptemp, float* ttemp)
{
  float sum = 0;
  for (int i = 0; i < N; i++)
  {
    sum += arr[i];
    if (sum != res[i])
    {
      printf("FAIL: res[%d] - %0.0f does not equal %0.0f\n", i, res[i], sum);
      exit(1);
    }
  }
  printf("SUCCESS! All prefix sums added correctly.\n");
}

int main()
{
  const int N = 1000000;
  size_t size = N * sizeof(float);

  float *arr;
  float *res;

  cudaMallocManaged(&arr, size);
  cudaMallocManaged(&res, size);

  initWith(2, arr, N);
  initWith(0, res, N);

  int blocks = 1;
  int threadsPerBlock = 32;
  int totalThreads = blocks * threadsPerBlock;

  float *ptemp;
  float *ttemp;
  cudaMallocManaged(&ptemp, totalThreads * sizeof(float));
  cudaMallocManaged(&ttemp, totalThreads * sizeof(float));

  scan<<<blocks, threadsPerBlock>>>(res,arr,N);
  cudaDeviceSynchronize();

  checkRes(arr, res, N, ptemp, ttemp);

  cudaFree(arr);
  cudaFree(res);
  cudaFree(ttemp);
  cudaFree(ptemp);
}