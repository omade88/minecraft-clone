project(minecraft-clone)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(src)
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})

file(GLOB_RECURSE SOURCES 
    src/*.cpp 
    src/engine/*.cpp 
    src/world/*.cpp 
    src/player/*.cpp 
    src/utils/*.cpp
)

add_executable(minecraft-clone ${SOURCES})

# Link libraries
target_link_libraries(minecraft-clone 
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    glfw
    pthread
    dl
)

set(SHADER_FILES 
    shaders/vertex.glsl 
    shaders/fragment.glsl
)

# Copy shader files to build directory
add_custom_command(TARGET minecraft-clone POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:minecraft-clone>/shaders
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/shaders/vertex.glsl
        ${CMAKE_SOURCE_DIR}/shaders/fragment.glsl
        $<TARGET_FILE_DIR:minecraft-clone>/shaders/
)