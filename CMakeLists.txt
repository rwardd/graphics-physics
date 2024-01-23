cmake_minimum_required(VERSION 3.1)

project(physics_engine C CXX)

set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(OpenGL REQUIRED)

if (APPLE)
link_directories("/opt/homebrew/lib")
include_directories("/opt/homebrew/include")
endif()

include_directories(${OPENGL_INCLUDE_DIRS})

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")

include_directories(${PROJECT_NAME} "${PROJECT_SOURCE_DIR}/lib" "${PROJECT_SOURCE_DIR}/src")
set(GLAD_GL "${PROJECT_SOURCE_DIR}/lib/glad/gl.h")

add_executable(${PROJECT_NAME} src/Shader.cpp src/main.cpp ${GLAD_GL})
target_sources(${PROJECT_NAME} PRIVATE lib/gl.c)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw)
