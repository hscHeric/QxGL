cmake_minimum_required(VERSION 3.10)
project(QxGL VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Diretórios de include
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/stb)

# Encontrar pacotes necessários
find_package(OpenGL REQUIRED)

# Localizar GLUT
find_package(GLUT REQUIRED)


# Coleta dos arquivos fonte
file(GLOB_RECURSE QXGL_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Criação da biblioteca estática
add_library(qxgl STATIC ${QXGL_SOURCES})

# Links de bibliotecas
target_link_libraries(qxgl
    ${OPENGL_gl_LIBRARY}  # OpenGL
    ${GLUT_LIBRARIES}     # GLUT
    dl                    # Linux-only dynamic linker
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

