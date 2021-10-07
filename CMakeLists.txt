cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(fileManager LANGUAGES CXX)
add_executable(fileManager fileManager/filemanager.cpp fileManager/filemanager.h fileManager/main_fm.cpp)
target_link_libraries(fileManager pthread)

project(multMatrix LANGUAGES CXX)
add_executable(multMatrix multMatrix/multmatrix.cpp multMatrix/multmatrix.h multMatrix/main_multMatrix.cpp)
target_link_libraries(multMatrix pthread)