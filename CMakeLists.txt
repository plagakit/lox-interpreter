cmake_minimum_required (VERSION 3.8)

project (cpplox
	LANGUAGES CXX
	VERSION 0.1
)

# Use C++17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Let target_sources() look for relative file paths instead of absolute
cmake_policy(SET CMP0076 NEW)

add_subdirectory(src)
