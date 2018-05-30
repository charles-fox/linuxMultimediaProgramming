SET(CMAKE_CXX_FLAGS "-std=c++11")
cmake_minimum_required(VERSION 2.8)
project( test1 )
find_package( OpenCV REQUIRED )
add_executable( test1 test1.cpp )
target_link_libraries( test1 cairo )

