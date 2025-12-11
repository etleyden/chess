cmake_minimum_required(VERSION 3.10)
project(Chess)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Automatically find all board source files (including subdirectories)
file(GLOB_RECURSE BOARD_SOURCES 
    "${CMAKE_SOURCE_DIR}/src/board/*.cpp"
)

# Print found sources for debugging
message(STATUS "Searching in: ${CMAKE_SOURCE_DIR}/src/board/")
message(STATUS "Found board sources: ${BOARD_SOURCES}")

# Verify we found files
if(NOT BOARD_SOURCES)
    message(FATAL_ERROR "No .cpp files found in src/board/ directory! Check your directory structure.")
endif()

# Add library target
add_library(chess_lib ${BOARD_SOURCES})

# Add include directories
target_include_directories(chess_lib PUBLIC 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/board
)

# Automatically find all test files
file(GLOB TEST_SOURCES "${CMAKE_SOURCE_DIR}/test/*.cpp")

# Print found test sources for debugging
message(STATUS "Searching in: ${CMAKE_SOURCE_DIR}/test/")
message(STATUS "Found test sources: ${TEST_SOURCES}")

# Verify we found test files
if(NOT TEST_SOURCES)
    message(WARNING "No .cpp files found in test/ directory!")
endif()

# Test executable
add_executable(board_tests ${TEST_SOURCES})

target_include_directories(board_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/board
    ${CMAKE_SOURCE_DIR}/test
)

target_link_libraries(board_tests PRIVATE chess_lib)

# Custom target to build and run tests
add_custom_target(run_tests
    COMMAND board_tests
    DEPENDS board_tests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running chess board tests..."
)

# Install the library
install(TARGETS chess_lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install headers
install(FILES src/chess.hpp DESTINATION include)
install(DIRECTORY src/board/ DESTINATION include/board 
    FILES_MATCHING PATTERN "*.hpp"
    PATTERN "*.cpp" EXCLUDE
)