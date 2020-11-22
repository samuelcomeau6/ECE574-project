cmake_minimum_required(VERSION 3.10)

project(hlsyn VERSION 0.1)

add_executable(hlsyn main.cpp parse.cpp path.cpp graph.cpp scheduling.cpp verilog.cpp hlsm.cpp)
#configure_file(verilog_template.vh verilog_template.vh COPYONLY)
target_include_directories(hlsyn PUBLIC "${PROJECT_BINARY_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "-std=gnu++11")