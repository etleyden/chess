cmake_minimum_required(VERSION 3.10)
project(Chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SRC_FILES
    src/board/board.cpp
)

# Add library target
add_library(chess_lib ${SRC_FILES})

# Add include directories
target_include_directories(chess_lib PUBLIC src)

# Add test executable
add_executable(test_suite test/board_test.cpp)
target_link_libraries(test_suite chess_lib)

# Add a custom command to build and run tests
add_custom_target(run_tests
    COMMAND test_suite
    DEPENDS test_suite
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Install the library
install(TARGETS chess_lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.hpp")