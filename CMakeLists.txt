cmake_minimum_required(VERSION 3.0)

project(OSM-examples)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Osmium REQUIRED COMPONENTS io sparsehash)

add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "-O3 -g")

add_executable(utcak utcak.cpp)
target_link_libraries(utcak ${OSMIUM_LIBRARIES})

add_executable(buszjarat buszjarat.cpp)
target_link_libraries(buszjarat ${OSMIUM_LIBRARIES})

