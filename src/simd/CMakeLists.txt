add_executable(bench_simd simd.cpp my_cpuid.h)
#target_link_libraries(bench_simd PRIVATE benchmark::benchmark benchmark::benchmark_main)
