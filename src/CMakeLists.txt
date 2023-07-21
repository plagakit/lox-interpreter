add_executable(cpp-lox)

target_include_directories(cpp-lox
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(cpp-lox
	PUBLIC
		main.cpp
	PRIVATE
		lox.cpp
)