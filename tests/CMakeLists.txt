add_executable(lox_tests
	test_utils.h
	scanner_test.cpp
	expression_test.cpp
	statement_test.cpp
)

target_link_libraries(
	lox_tests
	GTest::gtest_main
	cpplox
)

include(GoogleTest)
gtest_discover_tests(lox_tests)