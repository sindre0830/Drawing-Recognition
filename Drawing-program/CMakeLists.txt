cmake_minimum_required(VERSION 3.15)

project(drawing-recognition)

find_package(OpenGL REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

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
  ${PYTHON_LIBRARIES}
)
