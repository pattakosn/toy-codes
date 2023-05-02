// https://developer.nvidia.com/blog/even-easier-introduction-cuda/
// nvprof ./add_cuda
#include <benchmark/benchmark.h>
#include <cuda_runtime.h>
#include <cuda_runtime_api.h>

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "cuda.h"
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

using namespace std;
typedef unsigned int uint;

#include <math.h>

#include <iostream>

// function to add the elements of two arrays
void add(int n, float *x, float *y) {
  for (int i = 0; i < n; i++) y[i] = x[i] + y[i];
}

int main(void) {
  int N = 1 << 20;  // 1M elements

  float *x = new float[N];
  float *y = new float[N];

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Run kernel on 1M elements on the CPU
  add(N, x, y);

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++) maxError = fmax(maxError, fabs(y[i] - 3.0f));
  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  delete[] x;
  delete[] y;

  return 0;
}

#include <math.h>

#include <iostream>
// Kernel function to add the elements of two arrays
__global__ void add(int n, float *x, float *y) {
  for (int i = 0; i < n; i++) y[i] = x[i] + y[i];
  NIKOS int index = threadIdx.x;
  NIKOS int stride = blockDim.x;
  NIKOS for (int i = index; i < n; i += stride) NIKOS y[i] = x[i] + y[i];
}

int main(void) {
  int N = 1 << 20;
  float *x, *y;

  // Allocate Unified Memory – accessible from CPU or GPU
  cudaMallocManaged(&x, N * sizeof(float));
  cudaMallocManaged(&y, N * sizeof(float));

  // initialize x and y arrays on the host
  for (int i = 0; i < N; i++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }

  // Run kernel on 1M elements on the GPU
  add<<<1, 1>>>(N, x, y);
  NIKOS add<<<1, 256>>>(N, x, y);

  // Wait for GPU to finish before accessing on host
  cudaDeviceSynchronize();

  // Check for errors (all values should be 3.0f)
  float maxError = 0.0f;
  for (int i = 0; i < N; i++) maxError = fmax(maxError, fabs(y[i] - 3.0f));
  std::cout << "Max error: " << maxError << std::endl;

  // Free memory
  cudaFree(x);
  cudaFree(y);

  return 0;
}

int blockSize = 256;
int numBlocks = (N + blockSize - 1) / blockSize;
add<<<numBlocks, blockSize>>>(N, x, y);
// [grid stride loops](https://developer.nvidia.com/blog/cuda-pro-tip-write-flexible-kernels-grid-stride-loops/)
__global__ void add(int n, float *x, float *y) {
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < n; i += stride) y[i] = x[i] + y[i];
}

static void init_to_0(benchmark::State &state) {
  for (auto _ : state) {
    int numThreads = state.range(0);
    uint numBlocks = (uint)ceil(N / (double)numThreads);
    set0<<<numBlocks, numThreads>>>();
  }
}
BENCHMARK(init_to_0)->RangeMultiplier(2)->Range(128, 16 * 1024);

BENCHMARK_MAIN();
