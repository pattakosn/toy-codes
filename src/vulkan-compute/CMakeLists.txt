find_package(Vulkan)
if(NOT Vulkan_FOUND)
    message(STATUS "[Vulkan] not found, skipping Vulkan examples")
else()
    add_custom_command(OUTPUT "${CMAKE_BINARY_DIR}/Square.spv"
            COMMAND $ENV{VK_SDK_PATH}/Bin/dxc -T cs_6_0 -E "Main" -spirv -fvk-use-dx-layout -fspv-target-env=vulkan1.1 -Fo "${CMAKE_BINARY_DIR}/Square.spv" "Square.hlsl"
            DEPENDS "Square.hlsl"
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Compiling Shaders"
    )
    add_custom_target(ComputeShader DEPENDS "${CMAKE_BINARY_DIR}/Square.spv")

    add_executable(VulkanCompute vulkan-compute.cpp)
    target_link_libraries(VulkanCompute PRIVATE Vulkan::Vulkan)
    add_dependencies(VulkanCompute ComputeShader)
endif()