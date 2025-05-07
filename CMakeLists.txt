cmake_minimum_required(VERSION 3.10)
project(MyCppProject VERSION 1.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(EXPORT_COMPILE_COMMANDS ON)
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)