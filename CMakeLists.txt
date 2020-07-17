cmake_minimum_required(VERSION 3.1...3.16)
project(ReductionLibrary VERSION 1.0 LANGUAGES C;CXX)
find_package(openPMD 0.9.0 CONFIG)



add_executable(Reduction src/main.cpp)
if(openPMD_FOUND)
    target_link_libraries(Reduction PRIVATE openPMD::openPMD)
endif()
target_include_directories(Reduction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
message(${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_include_directories(Reduction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
