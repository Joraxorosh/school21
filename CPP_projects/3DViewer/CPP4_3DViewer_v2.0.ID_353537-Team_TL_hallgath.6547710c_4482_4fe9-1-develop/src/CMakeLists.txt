cmake_minimum_required(VERSION 3.16)
project(CpuStaticViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Gui OpenGL OpenGLWidgets)
find_package(GTest REQUIRED)


add_subdirectory(core)
add_subdirectory(parser)
add_subdirectory(render)
add_subdirectory(view)
add_subdirectory(resources)
add_subdirectory(test)
add_subdirectory(settings)
add_subdirectory(gif)

add_executable(gpu_viewer
        run_program.cpp
)

target_link_libraries(gpu_viewer PUBLIC core view parser gl_render Qt6::Widgets Qt6::Gui Qt6::OpenGLWidgets)


add_executable(run_test run_tests.cpp)
target_link_libraries(run_test PRIVATE core view parser gl_render Qt6::Widgets Qt6::Gui Qt6::OpenGLWidgets GTest::gtest
)
