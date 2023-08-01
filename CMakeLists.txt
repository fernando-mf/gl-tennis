cmake_minimum_required(VERSION 3.11)

project(assignment_2)

include(ExternalProject)

# Set install directory
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/dist CACHE PATH ${CMAKE_SOURCE_DIR}/dist FORCE)
set(CMAKE_BUILD_TYPE "Debug")
if (WIN32)
    set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "Debug" FORCE)
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)

include(BuildGLEW)
include(BuildGLFW)
include(BuildGLM)

# assignment 2
set(EXEC assignment2)

file(GLOB SRC src/*.cpp)

add_executable(${EXEC} ${SRC} src/Cube.cpp src/Cube.h src/RacketFernando.cpp src/RacketFernando.h src/ArmWithRacketFernando.cpp src/ArmWithRacketFernando.h src/TexturedColorVertex.cpp src/TexturedColorVertex.h src/ShaderProgram.cpp src/ShaderProgram.h include/stb_image.h src/SphereFernando.cpp src/SphereFernando.h)

target_include_directories(${EXEC} PRIVATE include)

target_link_libraries(${EXEC} OpenGL::GL glew_s glfw glm)

list(APPEND BIN ${EXEC})
# end assignment 2

# install files to install location
install(TARGETS ${BIN} DESTINATION ${CMAKE_INSTALL_PREFIX})

# copy assets
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        COMMENT "Copying assets to ${CMAKE_CURRENT_BINARY_DIR}/assets")

add_dependencies(${EXEC} copy_assets)