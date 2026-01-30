add_subdirectory(imgui)

add_executable(sdl3_imgui 
    main.cpp
    gui.cpp gui.h)
target_link_libraries(sdl3_imgui PRIVATE imgui)
