#include "test/test_affine.h"
#include "test/test_parser.h"

#include <gtest/gtest.h>
int main() {
	std::cout << "Running tests\n";
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}