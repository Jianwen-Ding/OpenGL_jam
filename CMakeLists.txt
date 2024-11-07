cmake_minimum_required(VERSION 3.13.4)

project(GLJam)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define sources (main.cpp and all .c and .cpp files in the src/ folder)
file(GLOB_RECURSE CPP_SOURCES ./src/*.cpp)
file(GLOB_RECURSE C_SOURCES ./src/*.c)

# actually create executable
add_executable(${PROJECT_NAME} main.cpp ${CPP_SOURCES} ${C_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/glm-master
    ${CMAKE_SOURCE_DIR}/include/glm-master/glm
    ${CMAKE_SOURCE_DIR}/include/glad
    ${CMAKE_SOURCE_DIR}/include/assimp
)

# Link libraries
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 dl)

find_package(assimp REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)