cmake_minimum_required(VERSION 3.10)
project(MacosOpenGL)

set(project "MacosOpenGL")

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${project} ${SOURCES} ${HEADERS})

target_link_libraries(${project} OpenGL::GL GLEW::GLEW glfw)