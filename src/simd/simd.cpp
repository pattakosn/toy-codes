//#include <benchmark/benchmark.h>
#include <array>
#include <cpuid.h>
#include "my_cpuid.h"
#include "immintrin.h"

static std::string get_cpu_name()
{
        MY_CPUID cpuID(0); // Get CPU vendor

        std::string vendor;
        vendor += std::string((const char *)&cpuID.EBX(), 4);
        vendor += std::string((const char *)&cpuID.EDX(), 4);
        vendor += std::string((const char *)&cpuID.ECX(), 4);
        return vendor;
}
//static void inline_assembly(benchmark::State &state) {
//        std::cout <<"cpu found: " << get_cpu_name() << std::endl;
//        for (auto _ : state)
//                ;
//}
//BENCHMARK(inline_assembly);
//
//BENCHMARK_MAIN();

void multiply_vectors() {
        float f1[] = {1., 2., 3., 4.};
        float f2[] = {4., 3., 2., 1.};
        std::array res{0.f, 0.f, 0.f, 0.f};
        _asm
        {
                movups xmm1, f1;
                movups xmm2. f2;
                mulps xmm1, xmm2;
                movups res, xmm1;
        }
        std::cout << std::endl;
        for(size_t i = 0; i < res.size(); ++i)
                std::cout << "res[ " << i << " ]= " << res[i] << std::endl;
        std::cout << std::endl;
}

void report_sse_support() {
        int d, c;
        _asm
        {
                mov eax, 1;
                cpuid;
                mov d, edx;
                mov c, ecx;
        }
        if((d & (1<<26)) != 0)
                std::cout << "SSE2 supported" << std::endl;
        if((c & 1) != 0)
                std::cout << "SSE3 supported" << std::endl;
        if((c & (1<<19)) != 0)
                std::cout << "SSE4.1 supported" << std::endl;
        if((c & (1<<20)) != 0)
                std::cout << "SSE4.2 supported" << std::endl;
}

std::string get_cpu_name_intrinsics() {
        //int cpuidInfo[4];
        //__cpuid(cpuIdInfo, 1);
        auto a = _mm_set_ps(1., 2., 3., 4.);
        auto b = _mm_set_ps(4, 3, 2, 1);
        auto c = _mm_add_ps(a, b);
        //auto res = c.m128_f32[0];
        __try {
                __m256 z = _mm256_set_pd(1., 2., 3., 4.);
        } __except (1) {
                std::cout << "sorry, not sorry" <<std::endl;
        }
}
int main(int, char*[]) {
        std::cout <<"cpu found: " << get_cpu_name() << std::endl;

        multiply_vectors();

        report_sse_support();

        std::cout <<"cpu found: " << get_cpu_name_intrinsics() << std::endl;

        return EXIT_SUCCESS;
}
