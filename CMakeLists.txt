cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

project(fileManagerEXEC LANGUAGES CXX)
add_executable(fileManagerEXEC fileManager/filemanager.cpp fileManager/filemanager.h fileManager/main_fm.cpp)
target_link_libraries(fileManagerEXEC pthread)

project(multMatrixEXEC LANGUAGES CXX)
add_executable(multMatrixEXEC multMatrix/multmatrix.cpp multMatrix/multmatrix.h multMatrix/main_multMatrix.cpp multMatrix/mainPR1Server.cpp 
    multMatrix/mainPR1Client.cpp multMatrix/multmatrix_imp.cpp multMatrix/multmatrix_imp.h multMatrix/multmatrix_stub.cpp multMatrix/multmatrix_stub.h
    multMatrix/utils.cpp multMatrix/utils.h)
target_link_libraries(multMatrixEXEC pthread)
