add_executable(bench_string_trimming main_string_trimmming.cpp)
target_link_libraries(bench_string_trimming benchmark::benchmark Boost::boost)

add_executable(bench_eigen_AxEQbLU main_axEQb.cpp)
target_link_libraries(bench_eigen_AxEQbLU Eigen3::Eigen benchmark::benchmark OpenMP::OpenMP_CXX)
