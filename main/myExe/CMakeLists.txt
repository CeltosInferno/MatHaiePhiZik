cmake_minimum_required(VERSION 3.10)

set(MY_EXE_SOURCES src/main.cpp) # src/test_particle.cpp instead if you want to test

add_executable(MyExe ${MY_EXE_SOURCES})
target_link_libraries(MyExe PUBLIC MyLib)

add_executable(TestParticle src/test_particle.cpp)
target_link_libraries(TestParticle PUBLIC MyLib)

add_executable(TestVector3D src/test_vector3d.cpp)
target_link_libraries(TestVector3D PUBLIC MyLib)