cmake_minimum_required(VERSION 3.1...3.16)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(_TARGET_NAME ReductionLibrary)
project(${_TARGET_NAME} VERSION 1.0 LANGUAGES C;CXX)
find_package(openPMD 0.9.0 CONFIG)
find_package(alpaka REQUIRED)


alpaka_add_executable(${_TARGET_NAME} src/main.cpp)
if(openPMD_FOUND)
    target_link_libraries(${_TARGET_NAME} PRIVATE openPMD::openPMD)
endif()
target_include_directories(${_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
message(${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(${_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(
  ${_TARGET_NAME}
  PUBLIC alpaka::alpaka)
