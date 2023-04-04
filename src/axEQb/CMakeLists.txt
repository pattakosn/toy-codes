add_executable(bench_eigen_AxEQbLU axEQb.cpp)
target_link_libraries(bench_eigen_AxEQbLU PRIVATE Eigen3::Eigen benchmark::benchmark benchmark::benchmark_main OpenMP::OpenMP_CXX)
