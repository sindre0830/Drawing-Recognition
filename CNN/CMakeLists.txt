# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.8)

# Name of the project
project(cnn VERSION 1.0 LANGUAGES CXX)

# Add all the source files needed to build the executable
add_executable(cnn Src/main.cpp Library/zeromq.cpp)

configure_file(cnnConfig.h.in cnnConfig.h)

target_include_directories(cnn PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(mlpack REQUIRED)

#find cppzmq wrapper, installed by make of cppzmq
find_package(Armadillo REQUIRED)
find_package(cppzmq REQUIRED)
find_package(OpenMP REQUIRED)

# library
#add_subdirectory(libraries/MyLibrary)

# Link the executable and the library together
target_link_libraries(cnn /usr/local/lib64/libmlpack.so /usr/lib64/libarmadillo.so cppzmq OpenMP::OpenMP_CXX)
add_compile_options(-Wall -Wextra -O3 -DNDEBUG -fopenmp)