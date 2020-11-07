cmake_minimum_required(VERSION 3.10)

project(dpgen VERSION 0.1)

add_executable(dpgen main.cpp parse.cpp path.cpp critical_path.cpp)
configure_file(verilog_template.vh verilog_template.vh COPYONLY)
target_include_directories(dpgen PUBLIC "${PROJECT_BINARY_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
