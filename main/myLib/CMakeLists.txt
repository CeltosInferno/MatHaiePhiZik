cmake_minimum_required(VERSION 3.10)

set(MY_LIB_SOURCES 
	src/world.cpp 
	src/particle.cpp 
	src/vector3d.cpp 
	src/forceRegister.cpp 
	src/particleGravityGenerator.cpp 
	src/particleDragGenerator.cpp 
	src/particleString.cpp 
	src/particleAnchoredString.cpp 
	src/particleFloatingGenerator.cpp 
	src/particleElasticString.cpp 
	src/particleStiffSpring.cpp
	src/particleContact.cpp
	src/graphicRenderer.cpp
	src/mainLoop.cpp
	src/particleContactResolver.cpp
	src/particleLink.cpp
	src/particleCable.cpp
	src/particleRod.cpp
	src/quaternion.cpp
	src/matrix3.cpp
	src/rigidBody.cpp
	src/rigidBodyGravityGenerator.cpp
	src/rigidBodyAnchoredString.cpp
	src/rigidBodyDragGenerator.cpp
	src/rigidBodyElasticString.cpp
	src/rigidBodyFloatingGenerator.cpp
	src/rigidBodyStiffSpring.cpp
	src/rigidBodyString.cpp
	src/matrix4.cpp
	src/narrowSpace.cpp
	src/octree.cpp
	src/octreeNode.cpp
	src/primitive.cpp
	src/plane.cpp)

set(MY_LIB_HEADERS 
	include/world.hpp 
	include/particle.hpp 
	include/vector3d.hpp 
	include/forceRegister.hpp 
	include/particleForceGenerator.hpp 
	include/particleGravityGenerator.hpp 
	include/particleDragGenerator.hpp 
	include/particleString.hpp 
	include/particleAnchoredString.hpp 
	include/particleFloatingGenerator.hpp 
	include/particleElasticString.hpp 
	include/particleStiffSpring.hpp
	include/particleContact.hpp
	include/graphicRenderer.hpp
	include/mainLoop.hpp
	include/particleContactResolver.hpp
	include/particleContactGenerator.hpp
	include/particleLink.hpp
	include/particleCable.hpp
	include/particleRod.hpp
	include/quaternion.hpp
	include/matrix3.hpp
	include/rigidBody.hpp
	include/rigidBodyForceGenerator.hpp
	include/rigidBodyGravityGenerator.hpp
	include/rigidBodyAnchoredString.hpp
	include/rigidBodyDragGenerator.hpp
	include/rigidBodyElasticString.hpp
	include/rigidBodyFloatingGenerator.hpp
	include/rigidBodyStiffSpring.hpp
	include/rigidBodyString.hpp
	include/matrix4.hpp
	include/narrowSpace.hpp
	include/octree.hpp
	include/octreeNode.hpp
	include/primitive.hpp
	include/plane.hpp)


add_library(MyLib STATIC ${MY_LIB_SOURCES} ${MY_LIB_HEADERS})
target_include_directories(MyLib SYSTEM INTERFACE include)
target_include_directories(MyLib PRIVATE include)

target_link_libraries(MyLib PUBLIC GladLib glfw glm )