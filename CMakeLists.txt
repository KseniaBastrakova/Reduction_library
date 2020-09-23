cmake_minimum_required(VERSION 3.1...3.16)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(_PROJECT_TARGET_NAME ReductionProject)
set(_LIB_TARGET_NAME ReductionLibrary)
set(_EXE_TARGET_NAME ReductionExe)


project(${_PROJECT_TARGET_NAME} VERSION 1.0 LANGUAGES C;CXX)
find_package(openPMD 0.9.0 CONFIG)
find_package(alpaka REQUIRED)

alpaka_add_library(${_LIB_TARGET_NAME} INTERFACE) 
target_include_directories(${_LIB_TARGET_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/)

alpaka_add_executable(${_EXE_TARGET_NAME} src/main.cpp)

if(openPMD_FOUND)
    target_link_libraries(${_LIB_TARGET_NAME} PRIVATE openPMD::openPMD)
    target_link_libraries(${_EXE_TARGET_NAME} PRIVATE openPMD::openPMD)
endif()


target_include_directories(${_EXE_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
message(${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(${_EXE_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
target_link_libraries(
  ${_EXE_TARGET_NAME}
  PUBLIC alpaka::alpaka)
  
target_link_libraries(
  ${_LIB_TARGET_NAME}
  PUBLIC alpaka::alpaka)
