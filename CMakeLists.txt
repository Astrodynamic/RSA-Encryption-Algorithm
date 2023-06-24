cmake_minimum_required(VERSION 3.5)

project(RSA VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  ${CMAKE_SOURCE_DIR}/ainterface
  ${CMAKE_SOURCE_DIR}/interface
  ${CMAKE_SOURCE_DIR}/model
)

set(HEADERS
  ainterface/ainterface.h
  interface/interface.h
  model/rsa.h
)

set(SOURCES
  ainterface/ainterface.cc
  interface/interface.cc
  model/rsa.cc
)

add_executable(
  ${PROJECT_NAME}
  ${HEADERS}
  ${SOURCES}
  main.cc
)

target_compile_options(
  ${PROJECT_NAME}
  PRIVATE
  -Wall
  -Werror
  -Wextra
  -Wpedantic
  -fsanitize=address
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  -fsanitize=address
)