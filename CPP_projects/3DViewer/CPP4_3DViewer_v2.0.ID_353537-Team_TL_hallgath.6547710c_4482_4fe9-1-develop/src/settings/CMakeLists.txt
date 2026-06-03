add_library(settings STATIC
        settings.cpp
)

target_link_libraries(settings
        PUBLIC
        Qt6::Core
)

target_include_directories(settings
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..
)