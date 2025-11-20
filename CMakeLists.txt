cmake_minimum_required(VERSION 3.31)
project(ion-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(git-submodules.cmake)

set(ONDA ${CMAKE_SOURCE_DIR}/libraries/onda)
set(ONDA_ARDUINO ${CMAKE_SOURCE_DIR}/libraries/onda-arduino)
set(CMAKE_HELPERS ${CMAKE_SOURCE_DIR}/libraries/cmake-helpers)

add_subdirectory("libraries/onda")
add_subdirectory("libraries/onda-arduino")
add_subdirectory("libraries/ion-cpp")
add_subdirectory("ion-stdio")
add_subdirectory("tests/")