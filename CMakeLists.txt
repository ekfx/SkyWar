# CMakeLists.txt 
# This is my first CMakeLists.txt and I will put some 
# comments to understand and have notes about CMake.
# 
# Why I am using this? Yes, I confess, this is a suggest from AI 
# BUT their said this is more portable and easy to maintain, so 
# the AI shouldn't be the coder, but can and should help me to have
# better practices! :)

# this defines the minimun version of the cmake
cmake_minimum_required(VERSION 3.15)

# defines the name of the project and the langueges
project(UpRace LANGUAGES C CXX)

# define c++ version and set as requiremens
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# directory to the executable and binaries (yes thats professional)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# requires opengl and glfw3 pkg to run
find_package(OpenGL REQUIRED)
# find_package(glfw3 REQUIRED)

# shows which files to compile
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
    "src/imgui/*.cpp"
    "src/imgui/*.h"
    "src/imgui/*.hpp"
    "src/glad.c"
)

# create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# says where to find the headers
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/lib_mingw-w64
    src
)

# automatic link to libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    OpenGL::GL
    glfw3
    glfw3dll
)




