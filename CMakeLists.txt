cmake_minimum_required(VERSION 3.21)
 
project(my_project)
 
find_package(OpenGL REQUIRED)
add_library(glad lib/glad/src/glad.c)
target_include_directories(glad  PUBLIC lib/glad/include)
 
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl") 
 
add_executable(test src/test.cpp)
target_link_libraries(test glfw ${GL_LIBRARY} glad)

add_executable(triangle src/triangle.cpp)
target_link_libraries(triangle glfw ${GL_LIBRARY} glad)

add_executable(rectangle src/rectangle.cpp)
target_link_libraries(rectangle glfw ${GL_LIBRARY} glad)