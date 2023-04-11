// https://riptutorial.com/cuda/example/32764/very-simple-cuda-code
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "cuda.h"
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>

#include<cstdio>
#include <cmath>
#include<cstdlib>
#include<iostream>
#include <iomanip>

#include <benchmark/benchmark.h>


using namespace std;
typedef unsigned int uint;


const uint N = 1e6;

__device__ uint Val2[N];

__global__ void set0() {
    uint index = __mul24(blockIdx.x, blockDim.x) + threadIdx.x;
    if (index < N)
        Val2[index] = 0;
}


static void init_to_0(benchmark::State &state)
{
	for (auto _ : state) {
		int numThreads = state.range(0);
		uint numBlocks = (uint)ceil(N / (double)numThreads);
		set0 <<< numBlocks, numThreads >>>();
	}
}
BENCHMARK(init_to_0)->RangeMultiplier(2)->Range(32, 16*1024);

BENCHMARK_MAIN();
