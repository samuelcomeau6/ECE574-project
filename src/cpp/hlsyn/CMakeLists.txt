cmake_minimum_required(VERSION 3.10)

project(hlsyn VERSION 0.1)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.45.0 COMPONENTS filesystem regex)

if(Boost_FOUND)
    add_executable(hlsyn main.cpp parse.cpp path.cpp graph.cpp scheduling.cpp verilog.cpp hlsm.cpp)
    target_link_libraries(hlsyn Boost::filesystem Boost::regex)
endif()

target_include_directories(hlsyn PUBLIC "${PROJECT_BINARY_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "-std=gnu++11 -I/usr/include/boost/ -lboost_regex")