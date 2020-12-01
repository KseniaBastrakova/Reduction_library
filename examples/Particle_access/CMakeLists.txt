################################################################################
# Required CMake version.
################################################################################

cmake_minimum_required(VERSION 3.1...3.16)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(_PROJECT_TARGET_NAME Make_species)

project(${_PROJECT_TARGET_NAME} VERSION 1.0 LANGUAGES C;CXX)


set(ReductionLibrary_DIR /home/kseniia/Documents/Reduction_library_install/share/ReductionLibrary/cmake/)

find_package(ReductionLibrary CONFIG REQUIRED)
find_package(alpaka REQUIRED)

add_executable(${_PROJECT_TARGET_NAME} src/main.cpp)
target_include_directories(${_PROJECT_TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


if(alpaka_FOUND)
	message("alpaka found")
    target_link_libraries(${_PROJECT_TARGET_NAME} PUBLIC alpaka::alpaka)
endif()

if(ReductionLibrary_FOUND)
    message(STATUS "Found ReductionLibrary: ${ReductionLibrary_DIR}")
    
    message(STATUS ${ReductionLibrary_INCLUDE_DIR})
    message(STATUS "Found ReductionLibrary: include dirs ${ReductionLibrary_CONSIDERED_VERSIONS}")
    target_link_libraries(Make_species PUBLIC ReductionLibrary::ReductionLibrary)
   
else(ReductionLibrary_FOUND)
    message(STATUS "Could NOT find ReductionLibrary - set ReductionLibrary_DIR or check your CMAKE_PREFIX_PATH")
endif(ReductionLibrary_FOUND)
