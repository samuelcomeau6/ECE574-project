cmake_minimum_required(VERSION 3.10)

project(gvdpgen VERSION 0.0)

add_executable(gvdpgen main.cpp parse.cpp path.cpp)
configure_file(main.h.in main.h)
target_include_directories(gvdpgen PUBLIC "${PROJECT_BINARY_DIR}")