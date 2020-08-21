cmake_minimum_required(VERSION 3.5)

project(Vertex_Buffers_QT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
/media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/include
/media/liusheng/Programfiles/Programs/libs/glm/0.9.9.8
/media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/ubuntu/x86_64/include
)

add_library(${PROJECT_NAME})

LINK_DIRECTORIES(
#/media/liusheng/Programfiles/Programs/libs/glfw/glfw-3.3.2/src/libglfw.so
#/media/liusheng/Programfiles/Programs/VulkanSDK/1.1.114.0/ubuntu/x86_64/lib/libvulkan.so
)

add_executable(Vertex_Buffers_QT main.cpp)
target_link_libraries(Vertex_Buffers_QT ${PROJECT_NAME})
