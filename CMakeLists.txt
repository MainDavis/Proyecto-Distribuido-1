cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

project(fileManager1 LANGUAGES CXX)
add_executable(fileManager1 fileManager/filemanager.cpp fileManager/filemanager.h fileManager/main_fm.cpp)
target_link_libraries(fileManager1 pthread)

project(multMatrix1 LANGUAGES CXX)
add_executable(multMatrix1 multMatrix/multmatrix.cpp multMatrix/multmatrix.h multMatrix/main_multMatrix.cpp)
target_link_libraries(multMatrix1 pthread)
