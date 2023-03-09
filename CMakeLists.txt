cmake_minimum_required(VERSION 3.0.0)
project(opengl_test VERSION 0.1.0)
# define GL_SILENCE_DEPRECATION
add_definitions(-DGL_SILENCE_DEPRECATION)
include_directories(/usr/local/include)
include_directories(/opt/homebrew/include)

# compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# debug mode
set(CMAKE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -Wpedantic -g)
# no optimization
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

link_directories(/opt/homebrew/lib)
file(GLOB SOURCES
    main.cpp
    gsrc.cpp
)

add_executable(opengl_test ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

target_link_libraries(opengl_test
    "-framework glut"
    "-framework opengl"
    "-lglew"
)
