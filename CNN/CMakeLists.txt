cmake_minimum_required(VERSION 3.12)

project(CNN)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

add_executable(${PROJECT_NAME} 
    Src/main.cpp 
    Library/zeromq.cpp Library/Header/zeromq.h 
    Library/functionality.cpp Library/Header/functionality.h 
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Library/Header
)

find_package(mlpack REQUIRED)
find_package(Armadillo REQUIRED)
find_package(cppzmq REQUIRED)
find_package(OpenMP REQUIRED)
find_package(CURL REQUIRED) 

include_directories(${CURL_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} 
    /usr/local/lib64/libmlpack.so 
    /usr/lib64/libarmadillo.so 
    cppzmq 
    OpenMP::OpenMP_CXX 
    ${CURL_LIBRARIES} 
)

add_compile_options(-Wall -Wextra -O3 -DNDEBUG -fopenmp)
