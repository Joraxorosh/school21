add_library(view STATIC
        gl_widget.cpp
        gl_widget.h
        interface.cpp
        interface.h
)

target_link_libraries(view
        PUBLIC
        Qt6::Widgets
        Qt6::Gui
        Qt6::OpenGLWidgets
        Qt6::OpenGL
        Qt6::Core
        settings
        gif
        core
)