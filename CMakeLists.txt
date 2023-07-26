cmake_minimum_required (VERSION 3.8)

project (cpplox
	LANGUAGES CXX
	VERSION 0.1
)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Let target_sources() look for relative file paths instead of absolute
cmake_policy(SET CMP0076 NEW)

# Testing
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	enable_testing()
endif()

add_subdirectory(lib)
add_subdirectory(src)

if (BUILD_TESTING)
	add_subdirectory(tests)
endif()