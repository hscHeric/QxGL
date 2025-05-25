cmake_minimum_required(VERSION 3.10)
project(QxGL VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE QXGL_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(qxgl STATIC ${QXGL_SOURCES})

target_link_libraries(qxgl
    ${OPENGL_gl_LIBRARY}
    glfw
    GLEW
    SOIL2
    assimp
    dl     
)

# Instalação da lib e headers
install(TARGETS qxgl
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY src/
    DESTINATION include/qxgl
    FILES_MATCHING PATTERN "*.hpp"
)

