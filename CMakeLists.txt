cmake_minimum_required(VERSION 3.31)
project(ion-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(git-submodules.cmake)

add_subdirectory("libraries/ion-cpp")
add_subdirectory("ion-stdio")
add_subdirectory("tests/")