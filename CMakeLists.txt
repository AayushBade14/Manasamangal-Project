cmake_minimum_required(VERSION 3.10)
project(
  manasamangal
  VERSION 1.0
  DESCRIPTION "A tale of behula"
  LANGUAGES C CXX
)

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.9
)
FetchContent_MakeAvailable(glfw)

find_package(OpenGL REQUIRED)

add_subdirectory(glm)

add_library(
  glad
  STATIC
  ./glad/src/glad.c
)
target_include_directories(
  glad
  PUBLIC
  ./glad/include
)

add_executable(
  manasamangal
  main.cpp  
)
target_link_libraries(
  manasamangal
  PUBLIC
  OpenGL::GL
  glad
  glfw
  glm::glm
)
