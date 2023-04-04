add_executable(bench_string_trimming string_trimmming.cpp)
target_link_libraries(bench_string_trimming PRIVATE Boost::boost benchmark::benchmark benchmark::benchmark_main)
