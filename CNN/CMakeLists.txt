# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

# Name of the project
project(cnn VERSION 1.0)

# Add all the source files needed to build the executable
add_executable(cnn src/main.cpp client/client.cpp)

configure_file(cnnConfig.h.in cnnConfig.h)

target_include_directories(cnn PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(MLPACK REQUIRED)

add_executable(mlpack_sample src/main.cpp)
target_link_libraries(mlpack_sample ${MLPACK_LIBRARY})

#find cppzmq wrapper, installed by make of cppzmq
find_package(cppzmq)
target_link_libraries(cnn cppzmq)

# Include the directory where MyLibrary project is. Otherwise, we can't use the
# library
#add_subdirectory(libraries/MyLibrary)

# Link the executable and the library together
#target_link_libraries(zeromq MyLibrary)
