cmake_minimum_required(VERSION 3.31)
project(ion-cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(git-submodules.cmake)

set(ONDA ${CMAKE_SOURCE_DIR}/lib/onda/src/cpp)
set(ONDA_ARDUINO ${CMAKE_SOURCE_DIR}/lib/onda/src/arduino)
set(CMAKE_HELPERS ${CMAKE_SOURCE_DIR}/lib/cmake-helpers)
set(TRANSMISSION ${CMAKE_SOURCE_DIR}/lib/TransmissionArduino/src/cpp)
set(ION ${CMAKE_SOURCE_DIR}/src/cpp)

add_subdirectory(${ONDA})
add_subdirectory(${ONDA_ARDUINO})
add_subdirectory(${TRANSMISSION})
add_subdirectory(${ION})
add_subdirectory("ion-stdio")
add_subdirectory("tests/")