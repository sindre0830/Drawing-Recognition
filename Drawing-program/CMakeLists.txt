cmake_minimum_required(VERSION 3.15)

project(drawing-recognition)

if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tensorflow)
    make_directory(${CMAKE_SOURCE_DIR}/external/tensorflow)
endif()

if(UNIX AND NOT APPLE)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tensorflow)
        make_directory(${CMAKE_SOURCE_DIR}/external/tensorflow)
    endif()

    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tensorflow/lib/libtensorflow.so)
        file(
        DOWNLOAD
            https://github.com/Neargye/tensorflow/releases/download/v1.15.0/libtensorflow-cpu-linux-x86_64-1.15.0.tar.gz ${CMAKE_SOURCE_DIR}/external/tensorflow/linux.tar.gz
        STATUS
            status
        LOG
            log
        )
        list(GET status 0 status_code)
        list(GET status 1 status_string)
        if(NOT status_code EQUAL 0)
            message(FATAL_ERROR "error downloading tensorflow lib: ${status_string}" "${log}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${CMAKE_SOURCE_DIR}/external/tensorflow/linux.tar.gz WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/tensorflow)
        file(REMOVE ${CMAKE_SOURCE_DIR}/external/tensorflow/linux.tar.gz)
    endif()

elseif(APPLE)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tensorflow)
        make_directory(${CMAKE_SOURCE_DIR}/external/tensorflow)
    endif()
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tensorflow/lib/libtensorflow.so)
        file(
        DOWNLOAD
            https://github.com/Neargye/tensorflow/releases/download/v1.15.0/libtensorflow-cpu-darwin-x86_64-1.15.0.tar.gz ${CMAKE_SOURCE_DIR}/external/tensorflow/darwin.tar.gz
        STATUS
            status
        LOG
            log
        )
        list(GET status 0 status_code)
        list(GET status 1 status_string)
        if(NOT status_code EQUAL 0)
            message(FATAL_ERROR "error downloading tensorflow lib: ${status_string}" "${log}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${CMAKE_SOURCE_DIR}/external/tensorflow/darwin.tar.gz WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/tensorflow)
        file(REMOVE ${CMAKE_SOURCE_DIR}/external/tensorflow/darwin.tar.gz)
    endif()

elseif(WIN32)
    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tensorflow)
        make_directory(${CMAKE_SOURCE_DIR}/external/tensorflow)
    endif()

    if (NOT EXISTS ${CMAKE_SOURCE_DIR}/external/tensorflow/lib/tensorflow.dll)
        file(
        DOWNLOAD
            https://github.com/Neargye/tensorflow/releases/download/v1.15.0/libtensorflow-cpu-windows-x86_64-1.15.0.zip ${CMAKE_SOURCE_DIR}/external/tensorflow/windows.zip
        STATUS
            status
        LOG
            log
        )
        list(GET status 0 status_code)
        list(GET status 1 status_string)
        if(NOT status_code EQUAL 0)
            message(FATAL_ERROR "error downloading tensorflow lib: ${status_string}" "${log}")
        endif()

        execute_process(COMMAND ${CMAKE_COMMAND} -E tar xvzf ${CMAKE_SOURCE_DIR}/external/tensorflow/windows.zip WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/external/tensorflow)
        file(REMOVE ${CMAKE_SOURCE_DIR}/external/tensorflow/windows.zip)
    endif()

    configure_file(external/tensorflow/lib/tensorflow.dll ${CMAKE_CURRENT_BINARY_DIR}/tensorflow.dll COPYONLY)
    configure_file(external/tensorflow/lib/tensorflow.dll ${CMAKE_CURRENT_BINARY_DIR}/test/tensorflow.dll COPYONLY)
endif()

include_directories(external/tensorflow/include)
link_directories(${CMAKE_SOURCE_DIR}/external/tensorflow/lib)

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external/glad)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)
add_subdirectory(external/freetype)

add_executable(${PROJECT_NAME}
	main.cpp
	const.h
	functions.h
	functions.cpp
	Colors.h
	Colors.cpp
	Paintbrush/Point.h
	Paintbrush/Point.cpp
	Paintbrush/Paintbrush.h
	Paintbrush/Paintbrush.cpp
	shaders/pointShader.h
	Navigation/Button.h
	Navigation/Button.cpp
	Navigation/ColorButton.h
	Navigation/ColorButton.cpp
    model.h model.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  glad
  glfw
  glm
  freetype
  OpenGL::GL
  tensorflow)
