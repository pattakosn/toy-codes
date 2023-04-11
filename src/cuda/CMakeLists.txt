if(NOT CMAKE_CUDA_COMPILER)
    message(WARNING "CUDA not found, skipping cuda test")
else()
    add_executable(cuda_test nvidia-seperate-compilation.cu particle.cu particle.h v3.cu v3.h)
    set_target_properties(cuda_test
        PROPERTIES
#        #CUDA_ARCHITECTURES "35;50;72;75"
        CUDA_ARCHITECTURES native
        CUDA_SEPARABLE_COMPILATION ON
        POSITION_INDEPENDENT_CODE ON
        CXX_STANDARD 17
        CUDA_STANDARD 17
)
#target_link_libraries(cuda_test)# PRIVATE benchmark::benchmark benchmark::benchmark_main)
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
     #set_target_properties(cuda_test PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
     #     set_target_properties(cuda_test PROPERTIES POSITION_INDEPENDENT_CODE ON)
     #set_property(TARGET cuda_test PROPERTY CUDA_RESOLVE_DEVICE_SYMBOLS ON)



    add_executable(bench_cuda_init_to_0 simple-bench.cu)
    target_link_libraries(bench_cuda_init_to_0 PRIVATE benchmark::benchmark benchmark::benchmark_main)
    set_target_properties(bench_cuda_init_to_0
        PROPERTIES
        CUDA_ARCHITECTURES native
)
endif()
