cmake_minimum_required (VERSION 3.8)

project (cpp-lox
	LANGUAGES CXX
	VERSION 0.1
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
