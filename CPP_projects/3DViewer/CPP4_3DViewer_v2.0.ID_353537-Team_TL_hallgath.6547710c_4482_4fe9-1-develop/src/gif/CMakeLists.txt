add_library(gif STATIC
            gif_recorder.cpp
            gif.h)

target_link_libraries(gif
        PUBLIC
        Qt6::Core
        Qt6::Widgets Qt6::Gui Qt6::OpenGLWidgets
)