cmake_minimum_required(VERSION 3.10)

project(QXGL LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLU REQUIRED)
find_package(GLUT REQUIRED)
find_package(assimp REQUIRED)
find_package(DevIL REQUIRED)

file(GLOB_RECURSE QXGL_SOURCES "src/*.cpp")

# Adicionar a biblioteca (pode ser STATIC ou SHARED)
add_library(qxgl STATIC ${QXGL_SOURCES})

# Adicionar o diretório 'src' como um diretório de include público.
# Isso permite que tanto a biblioteca quanto os exemplos encontrem os headers.
target_include_directories(qxgl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Linkar a biblioteca com suas dependências
target_link_libraries(qxgl PUBLIC
    OpenGL::GL
    OpenGL::GLU
    GLUT::GLUT
    assimp::assimp
    DevIL::IL
)
