cmake_minimum_required (VERSION 2.8)
project(OgreTutorialsSample)

set(CMAKE_CXX_STANDARD 11)

find_package(OGRE 1.11 REQUIRED COMPONENTS Bites RTShaderSystem)

file(COPY ${OGRE_CONFIG_DIR}/resources.cfg DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(0_Bootstrap Bootstrap.cpp)

target_link_libraries(0_Bootstrap OgreBites OgreRTShaderSystem)

add_executable(1_FirstScene BasicTutorial1.cpp)

target_link_libraries(1_FirstScene ${OGRE_LIBRARIES})

