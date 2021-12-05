cmake_minimum_required(VERSION 3.15)

project(drawing-recognition)

find_package(OpenGL REQUIRED)
find_package(PythonLibs REQUIRED)

include_directories(${PYTHON_INCLUDE_DIRS})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lzmq")

add_subdirectory(External/glad)
add_subdirectory(External/glfw)
add_subdirectory(External/glm)
add_subdirectory(External/freetype)

add_executable(${PROJECT_NAME}
	main.cpp Header/dictionary.h
	functionality.cpp Header/functionality.h
	Class/aboutScene.cpp Class/Header/aboutScene.h
	Class/button.cpp Class/Header/button.h
	Class/colorButton.cpp Class/Header/colorButton.h
	Class/endScene.cpp Class/Header/endScene.h
	Class/font.cpp Class/Header/font.h
	Class/gameScene.cpp Class/Header/gameScene.h
	Class/menuScene.cpp Class/Header/menuScene.h
    Class/model.cpp Class/Header/model.h
	Class/navButton.cpp Class/Header/navButton.h
	Class/paintbrush.cpp Class/Header/paintbrush.h
	Class/scene.cpp Class/Header/scene.h
	Class/sceneManager.cpp Class/Header/sceneManager.h
	Class/Shader/buttonShader.h
	Class/Shader/pointShader.h
	Class/Shader/textShader.h
)

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
