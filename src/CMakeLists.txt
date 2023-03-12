add_executable(bench_string_trimming string_trimmming.cpp)
target_link_libraries(bench_string_trimming PRIVATE Boost::boost benchmark::benchmark benchmark::benchmark_main)

add_executable(bench_eigen_AxEQbLU axEQb.cpp)
target_link_libraries(bench_eigen_AxEQbLU PRIVATE Eigen3::Eigen benchmark::benchmark benchmark::benchmark_main OpenMP::OpenMP_CXX)

add_executable(bench_simd simd.cpp)
target_link_libraries(bench_simd PRIVATE benchmark::benchmark benchmark::benchmark_main)