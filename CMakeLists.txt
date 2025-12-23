cmake_minimum_required(VERSION 3.10)
project(
  manasa
  VERSION 1.0
  DESCRIPTION "Manasamangal-Project"
  LANGUAGES C CXX
)

#---------------------------------------
# GLFW
#---------------------------------------

include(FetchContent)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.9
)

FetchContent_MakeAvailable(glfw)

#---------------------------------------
# ENGINE-TARGET
#---------------------------------------

add_executable(
main.cpp

  core/Application.cpp

  platform/glfw/GLFWWindow.cpp
)

#---------------------------------------
# INCLUDE-PATHS
#---------------------------------------

target_include_directories( manasa
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}
)

#---------------------------------------
# LINK-LIBRARIES
#---------------------------------------

target_link_libraries( manasa
  PRIVATE
  glfw 
)
