cmake_minimum_required(VERSION 3.10)

set(MY_EXE_SOURCES src/test_windows.cpp) # src/test_particle.cpp instead if you want to test

add_executable(MyExe ${MY_EXE_SOURCES})
target_link_libraries(MyExe PUBLIC MyLib GladLib glfw)