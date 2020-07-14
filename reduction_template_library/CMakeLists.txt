cmake_minimum_required(VERSION 3.1...3.16)
project(ReductionLibrary VERSION 1.0 LANGUAGES CXX)
find_package(openPMD 0.9.0 CONFIG)


file(GLOB_RECURSE sources      src/attribute/*.cpp src/attribute/*.h)
file(GLOB_RECURSE sources      src/*.cpp src/*.h)

add_executable(Reduction src/main.cpp)
if(openPMD_FOUND)
    target_link_libraries(Reduction PRIVATE openPMD::openPMD)
endif()
