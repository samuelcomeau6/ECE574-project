cmake_minimum_required(VERSION 3.10)

project(gvdpgen VERSION 0.0)


set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS filesystem regex) 

if(Boost_FOUND)
    add_executable(gvdpgen main.cpp parse.cpp path.cpp)

    target_link_libraries(gvdpgen Boost::filesystem Boost::regex)
endif()
target_include_directories(gvdpgen PUBLIC "${PROJECT_BINARY_DIR}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS "-std=gnu++11 -I/usr/include/boost/ -lboost_regex")
