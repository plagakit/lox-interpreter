# CMakeList.txt : CMake project for cpp-lox, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (cpp-lox "cpp-lox.cpp" "cpp-lox.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cpp-lox PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
