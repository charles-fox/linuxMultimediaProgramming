SET(CMAKE_CXX_FLAGS "-std=c++11")
cmake_minimum_required(VERSION 2.8)
project( videoWrite )
find_package( OpenCV REQUIRED )
add_executable( gl_sdl2_cube gl_sdl2_cube.cpp )
target_link_libraries( gl_sdl2_cube GL GLU SDL2  )

