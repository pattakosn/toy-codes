if(NOT CMAKE_CUDA_COMPILER)
    message(STATUS "[CUDA] not found, skipping cuda test")
else()
    add_executable(cuda_test nvidia-seperate-compilation.cu particle.cu particle.h v3.cu v3.h)
    set_target_properties(cuda_test
        PROPERTIES
        CUDA_ARCHITECTURES native
        CUDA_SEPARABLE_COMPILATION ON
        POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 20
        CUDA_STANDARD 20
    )
    target_include_directories(cuda_test
	     PRIVATE
	     ${CMAKE_CURRENT_SOURCE_DIR}/cuda/
	     ${CMAKE_CURRENT_SOURCE_DIR}/
	     INTERFACE
	     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/cuda/>
	     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
	     $<INSTALL_INTERFACE:include/example/cuda/>
	     )
    #set_property(TARGET cuda_test PROPERTY CUDA_ARCHITECTURES 75-real 75-virtual)
    #set_target_properties(cuda_test PROPERTIES CUDA_ARCHITECTURES "50;75")
    #target_compile_options("$<$<BUILD_INTERFACE:$<COMPILE_LANGUAGE:CXX>>:-fopenmp>$<$<BUILD_INTERFACE:$<COMPILE_LANGUAGE:CUDA>>:-Xcompiler=-fopenmp>")
    #target_compile_options(cuda_test PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:--generate-line-info>)
    #set_target_properties(cuda_testprj PROPERTIES CUDA_SEPARABLE_COMPILATION ON PROPERTIES POSITION_INDEPENDENT_CODE ON)
    #set_property(TARGET tgt PROPERTY CUDA_STANDARD 11)
    #set_property(TARGET CudaPTX PROPERTY CUDA_PTX_COMPILATION ON)
    #set_property(TARGET cuda_test PROPERTY CUDA_RESOLVE_DEVICE_SYMBOLS ON)

    #target_link_libraries(project CUDA::cudart)
    #target_link_libraries(project CUDA::cuda_driver)
    #install(TARGETS CudaPTX    OBJECTS DESTINATION bin/ptx )


    add_executable(bench_cuda_init_to_0 simple-bench.cu)
    target_link_libraries(bench_cuda_init_to_0 PRIVATE benchmark::benchmark benchmark::benchmark_main)
    set_target_properties(bench_cuda_init_to_0
        PROPERTIES
        CUDA_ARCHITECTURES native
    )


    add_executable(bench_cuda_grid_stride grid-stride.cu)
    target_link_libraries(bench_cuda_grid_stride PRIVATE benchmark::benchmark benchmark::benchmark_main)
    set_target_properties(bench_cuda_grid_stride
        PROPERTIES
        CUDA_ARCHITECTURES native
    )

    add_executable(cuda_mandelbrot cuda_mandelbrot.cu)
    #target_link_libraries(cuda_mandelbrot PRIVATE benchmark::benchmark benchmark::benchmark_main)
    target_compile_definitions(cuda_mandelbrot PRIVATE BENCHMARK)
endif()
