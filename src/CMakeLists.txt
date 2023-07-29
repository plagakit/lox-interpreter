# Compile lox as a library to be used by exe and unit tests
add_library(cpplox)

target_include_directories(cpplox
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(cpplox
	PUBLIC
		lox.cpp
		scanner.cpp
		parser.cpp
		interpreter.cpp
		token.cpp
		runtime_error.cpp
		utils.cpp
)

add_subdirectory(expr)
add_subdirectory(stmt)

# Actual executable
add_executable(lox-executable)
set_target_properties(lox-executable PROPERTIES OUTPUT_NAME lox)

target_include_directories(lox-executable
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(lox-executable PRIVATE main.cpp)
target_link_libraries(lox-executable PRIVATE cpplox)
