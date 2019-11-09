cmake_minimum_required(VERSION 3.10)

set(MY_EXE_SOURCES src/main.cpp) # src/test_particle.cpp instead if you want to test

add_executable(MyExe ${MY_EXE_SOURCES})
target_link_libraries(MyExe PUBLIC MyLib GladLib glfw)

add_executable(ExeV1 src/main_v1.cpp)
target_link_libraries(ExeV1 PUBLIC MyLib GladLib glfw)

add_executable(TestParticle src/test_particle.cpp)
target_link_libraries(TestParticle PUBLIC MyLib)

add_executable(TestVector3D src/test_vector3d.cpp)
target_link_libraries(TestVector3D PUBLIC MyLib)

add_executable(TestQuaternion src/test_quaternion.cpp)
target_link_libraries(TestQuaternion PUBLIC MyLib)

add_executable(TestMatrix src/test_matrix.cpp)
target_link_libraries(TestMatrix PUBLIC MyLib)

add_executable(TestRigidBody src/test_rigidBody.cpp)
target_link_libraries(TestRigidBody PUBLIC MyLib)