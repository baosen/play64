cmake_minimum_required(VERSION 3.2)
project(asm CXX)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-std=c++11)
endif()

include_directories(inc/asm)

# Add all .cpp-files in the source-directory.
FILE(GLOB_RECURSE SRC src/*.cpp)
add_library(asm ${SRC})

target_link_libraries(asm instr UnitTest++)

add_executable(asm-tests tests/tests.cpp)
target_link_libraries(asm-tests asm instr mem UnitTest++)

# Run tests as post build step.
add_custom_command(
    TARGET asm-tests 
	POST_BUILD COMMAND asm-tests
	COMMENT "Running tests...")
