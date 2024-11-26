cmake_minimum_required(VERSION 3.16)
project(AngryBird)
include_directories("src")

# Set the name of the executable to be produced
set(EXECUTABLE_NAME AngryBird)

# Add all .cpp - files under src/ directory
file(GLOB SOURCES src/*.cpp)
add_executable(${EXECUTABLE_NAME} ${SOURCES})
set(CMAKE_BUILD_TYPE Debug)

# Set C++ Standard
# set(CMAKE_CXX_STANDARD 11)

# Find the SFML package
# find_package(SFML 2.5 COMPONENTS network audio graphics window system REQUIRED)
# target_link_libraries(${EXECUTABLE_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)

# Find the Box2D package
# find_package(Box2D REQUIRED)
# target_link_libraries(${EXECUTABLE_NAME} Box2D)

# Box2d
# Include headers
include_directories(${CMAKE_SOURCE_DIR}/libs/box2d/include)
# Link the static library
target_link_libraries(${EXECUTABLE_NAME} ${CMAKE_SOURCE_DIR}/libs/box2d/lib/libbox2d.a)

# SFML
# Include headers
include_directories(${CMAKE_SOURCE_DIR}/libs/SFML/include)
# Find all the required SFML modules
set(SFML_LIBS
    ${CMAKE_SOURCE_DIR}/libs/SFML/lib/libsfml-audio-d.so
    ${CMAKE_SOURCE_DIR}/libs/SFML/lib/libsfml-graphics-d.so
    ${CMAKE_SOURCE_DIR}/libs/SFML/lib/libsfml-network-d.so
    ${CMAKE_SOURCE_DIR}/libs/SFML/lib/libsfml-system-d.so
    ${CMAKE_SOURCE_DIR}/libs/SFML/lib/libsfml-window-d.so
)
# Link the libraries
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBS} pthread dl)

# JSON
include_directories(${CMAKE_SOURCE_DIR}/libs/JSON)

# HTTP
include_directories(${CMAKE_SOURCE_DIR}/libs/HTTP)