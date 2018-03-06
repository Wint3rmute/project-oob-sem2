cmake_minimum_required(VERSION 3.2)
project(project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp headers/GameObject.h implementations/Bullet.cpp headers/Bullet.h utils/constants.h implementations/GameEngine.cpp headers/GameEngine.h implementations/Plane.cpp headers/Plane.h implementations/Skill.cpp headers/Skill.h implementations/Gun.cpp headers/Gun.h)
add_executable(project ${SOURCE_FILES})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(project ${SFML_LIBRARIES})
endif()