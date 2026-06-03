add_library(gl_render STATIC
            gl_render.cpp
            gl_shader_loader.cpp)

target_link_libraries(gl_render
        PUBLIC
        Qt6::Gui
        Qt6::OpenGL
)