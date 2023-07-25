add_executable(cpplox)

target_include_directories(cpplox
	PUBLIC
		${PROJECT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(cpplox
	PUBLIC
		main.cpp
	PRIVATE
		lox.cpp
		scanner.cpp
		token.cpp
		#parser.cpp
		utils.cpp
)

add_subdirectory(expr)
