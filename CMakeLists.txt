cmake_minimum_required(VERSION 3.2)
project(project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES src/main.cpp src/headers/GameObject.h src/implementations/Bullet.cpp src/headers/Bullet.h src/utils/constants.h src/implementations/GameEngine.cpp src/headers/GameEngine.h src/implementations/Plane.cpp src/headers/Plane.h src/implementations/Skill.cpp src/headers/Skill.h src/implementations/Gun.cpp src/headers/Gun.h src/implementations/Controller.cpp src/headers/Controller.h src/implementations/KeyboardController.cpp src/headers/KeyboardController.h src/implementations/DummyController.cpp src/headers/DummyController.h src/implementations/GameObject.cpp src/implementations/FieldOfView.cpp src/headers/FieldOfView.h src/implementations/NeuralNet.cpp src/headers/NeuralNet.h src/implementations/SynapseLayer.cpp src/headers/SynapseLayer.h src/utils/structs.h src/utils/functions.cpp src/implementations/RandomGenerator.cpp src/headers/RandomGenerator.h)

add_executable(project ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(project ${SFML_LIBRARIES})
endif()