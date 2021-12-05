cmake_minimum_required(VERSION 3.17)

project(CNN)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(CMAKE_CXX_FLAGS "-O3")

add_executable(${PROJECT_NAME} 
    Src/main.cpp 
    Library/zeromq.cpp Library/Header/zeromq.h 
    Library/functionality.cpp Library/Header/functionality.h 
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/Library/Header
)

find_package(Armadillo REQUIRED)
find_package(mlpack REQUIRED)
find_package(CURL REQUIRED) 
find_package(cppzmq REQUIRED)
find_package(OpenMP REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

include_directories(${ARMADILLO_INCLUDE_DIRS})
include_directories(${MLPACK_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} 
    ${ARMADILLO_LIBRARIES} 
    ${MLPACK_LIBRARIES} 
    ${CURL_LIBRARIES} 
    cppzmq 
    OpenMP::OpenMP_CXX 
    #${OpenCV_LIBS} 
)

add_compile_options(
    -DNDEBUG 
)
