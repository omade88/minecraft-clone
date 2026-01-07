project(minecraft-clone)

cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

file(GLOB_RECURSE SOURCES 
    src/*.cpp 
    src/engine/*.cpp 
    src/world/*.cpp 
    src/player/*.cpp 
    src/utils/*.cpp
)

add_executable(minecraft-clone ${SOURCES})

set(SHADER_FILES 
    shaders/vertex.glsl 
    shaders/fragment.glsl
)

add_custom_command(TARGET minecraft-clone POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${SHADER_FILES} $<TARGET_FILE_DIR:minecraft-clone>
)