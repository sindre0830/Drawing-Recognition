cmake_minimum_required(VERSION 3.15)

project(drawing-recognition)

find_package(OpenGL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_subdirectory(external/glm)

add_executable(${PROJECT_NAME}
	main.cpp
	const.h
	functions.h
	functions.cpp
	Point.h
	Point.cpp
	Paintbrush.h
	Paintbrush.cpp
	shaders/pointShader.h)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  glad
  glfw
  glm
  OpenGL::GL)
