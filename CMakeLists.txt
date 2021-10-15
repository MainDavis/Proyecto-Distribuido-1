cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ..)

project(fileManagerClient LANGUAGES CXX)
add_executable(fileManagerClient fileManager/filemanager.cpp fileManager/filemanager.h fileManager/main_fm.cpp)
target_link_libraries(fileManagerClient pthread)

project(fileManagerServer LANGUAGES CXX)
add_executable(fileManagerServer fileManager/filemanager.cpp fileManager/filemanager.h fileManager/main_fm.cpp)
target_link_libraries(fileManagerServer pthread)

project(multMatrixClient LANGUAGES CXX)
add_executable(multMatrixClient multMatrix/multmatrix.cpp multMatrix/multmatrix.h multMatrix/mainPR1Client.cpp 
    multMatrix/multmatrix_stub.cpp multMatrix/multmatrix_stub.h multMatrix/utils.cpp multMatrix/utils.h)
target_link_libraries(multMatrixClient pthread)

project(multMatrixServer LANGUAGES CXX)
add_executable(multMatrixServer multMatrix/multmatrix.cpp multMatrix/multmatrix.h multMatrix/mainPR1Server.cpp 
    multMatrix/multmatrix_imp.cpp multMatrix/multmatrix_imp.h multMatrix/utils.cpp multMatrix/utils.h)
target_link_libraries(multMatrixServer pthread)
