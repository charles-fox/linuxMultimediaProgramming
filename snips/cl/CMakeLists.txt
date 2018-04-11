cmake_minimum_required (VERSION 2.6)
project (Tutorial)


#defines OPENCL_LIBRARIES etc if sucessful
find_package( OpenCL REQUIRED )


add_executable(go go.cpp)

target_link_libraries(go  ${OpenCL_LIBRARIES} )

