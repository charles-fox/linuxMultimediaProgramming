SET(CMAKE_CXX_FLAGS "-std=c++11")
cmake_minimum_required(VERSION 2.8)
project( videoWrite )
find_package( OpenCV REQUIRED )
add_executable( texture texture.cpp )
target_link_libraries( texture GL GLU SDL2 SDL2_image )

