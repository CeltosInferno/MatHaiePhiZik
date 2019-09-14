cmake_minimum_required(VERSION 3.10)

set(GLAD_SOURCES src/glad.c)
set(GLAD_HEADERS include/glad/glad.h)

add_library(GladLib STATIC ${GLAD_SOURCES} ${GLAD_HEADERS})
target_include_directories(GladLib SYSTEM INTERFACE include)
target_include_directories(GladLib PRIVATE include)

target_link_libraries(GladLib PRIVATE)