cmake_minimum_required(VERSION 3.10)

set(MY_LIB_SOURCES src/world.cpp src/particle.cpp src/vector3d.cpp src/forceRegister.cpp src/particleGravityGenerator.cpp src/particleDragGenerator.cpp src/particleString.cpp src/particleAnchoredString.cpp src/particleFloatingGenerator.cpp src/particleElasticString.cpp)
set(MY_LIB_HEADERS include/world.hpp include/particle.hpp include/vector3d.hpp include/forceRegister.hpp include/particleForceGenerator.hpp include/particleGravityGenerator.hpp include/particleDragGenerator.hpp include/particleString.hpp include/particleAnchoredString.hpp include/particleFloatingGenerator.hpp include/particleElasticString.hpp)


add_library(MyLib STATIC ${MY_LIB_SOURCES} ${MY_LIB_HEADERS})
target_include_directories(MyLib SYSTEM INTERFACE include)
target_include_directories(MyLib PRIVATE include)

target_link_libraries(MyLib PRIVATE)