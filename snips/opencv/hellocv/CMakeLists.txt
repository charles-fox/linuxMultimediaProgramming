SET(CMAKE_CXX_FLAGS "-std=c++11")
cmake_minimum_required(VERSION 2.8)
project( helloCV )
find_package( OpenCV REQUIRED )
add_executable( hellocv hellocv.cpp )
target_link_libraries( hellocv ${OpenCV_LIBS} )

