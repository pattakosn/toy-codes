add_executable(bench_LU_eigen3 LU-eigen3.cpp)
target_link_libraries(bench_LU_eigen3 PRIVATE Eigen3::Eigen benchmark::benchmark benchmark::benchmark_main OpenMP::OpenMP_CXX)

add_executable(bench_LU_eigen3-mkl LU-eigen3-mkl.cpp)
target_link_libraries(bench_LU_eigen3-mkl PRIVATE Eigen3::Eigen benchmark::benchmark benchmark::benchmark_main MKL::MKL OpenMP::OpenMP_CXX)
