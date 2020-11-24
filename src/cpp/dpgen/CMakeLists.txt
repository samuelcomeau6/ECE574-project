cmake_minimum_required(VERSION 3.10)

project(dpgen VERSION 1.0)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem regex) 

if(Boost_FOUND)
    add_executable(dpgen main.cpp parse.cpp path.cpp critical_path.cpp)
    configure_file(verilog_template.vh verilog_template.vh COPYONLY)

    target_link_libraries(dpgen Boost::filesystem Boost::regex)
endif()
target_include_directories(dpgen PUBLIC "${PROJECT_BINARY_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "-std=gnu++11 -I/usr/include/boost/ -lboost_regex")