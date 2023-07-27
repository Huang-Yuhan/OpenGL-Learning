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

add_library(stb_image src/stb_image_wrapper.cpp)

add_executable(triangle_with_texture src/triangle_with_texture.cpp)
target_link_libraries(triangle_with_texture glfw ${GL_LIBRARY} glad stb_image)

add_executable(fpsmove src/fpsmove.cpp)
target_link_libraries(fpsmove glfw ${GL_LIBRARY} glad stb_image)