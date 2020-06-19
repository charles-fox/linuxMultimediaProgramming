SET(CMAKE_CXX_FLAGS "-std=c++11")
cmake_minimum_required(VERSION 2.8)
project(game)
find_package(SDL2 REQUIRED)
add_executable(game game.cpp)
target_link_libraries(game  SDL2)

