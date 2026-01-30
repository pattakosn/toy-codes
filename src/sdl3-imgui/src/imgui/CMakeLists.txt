add_library(imgui
    imgui.cpp imgui.h
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_impl_sdl3.cpp imgui_impl_sdl3.h
    imgui_impl_sdlrenderer3.cpp imgui_impl_sdlrenderer3.h
)
target_link_libraries(imgui PUBLIC SDL3::SDL3)
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})