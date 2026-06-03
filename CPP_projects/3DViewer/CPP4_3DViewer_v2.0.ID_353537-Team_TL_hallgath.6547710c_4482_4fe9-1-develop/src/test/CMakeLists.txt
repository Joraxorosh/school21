add_library(Tests STATIC
        test_affine.h
        test_parser.h
        )

target_link_libraries(Tests PRIVATE GTest::gtest_main GTest::gmock_main core
)