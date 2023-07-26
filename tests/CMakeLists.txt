add_executable(lox_tests
	scanner_test.cpp
)

target_link_libraries(
	lox_tests
	GTest::gtest_main
	cpplox
)

include(GoogleTest)
gtest_discover_tests(lox_tests)