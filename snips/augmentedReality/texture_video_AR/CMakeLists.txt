SET(CMAKE_CXX_FLAGS "-std=c++11")
cmake_minimum_required(VERSION 2.8)
project( ar )
find_package( OpenCV REQUIRED )
add_executable( ar ar.cpp )
target_link_libraries( ar GL GLU SDL2 SDL2_image ${OpenCV_LIBS} )
