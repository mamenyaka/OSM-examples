cmake_minimum_required(VERSION 3.0)

project(utcak)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(Osmium REQUIRED COMPONENTS io)

add_compile_options(-std=c++11)
set(CMAKE_CXX_FLAGS "-O3 -g")

add_executable(${PROJECT_NAME} utcak.cpp)
target_link_libraries(${PROJECT_NAME} ${OSMIUM_LIBRARIES})
