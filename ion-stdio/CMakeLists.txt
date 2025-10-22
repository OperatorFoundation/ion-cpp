cmake_minimum_required(VERSION 3.31)
project(ion-stdio)

set(CMAKE_CXX_STANDARD 17)

set(ION_STDIO_DIR ${CMAKE_SOURCE_DIR}/ion-stdio)
set(ION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/ion-cpp)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

add_executable(ion-stdio
  IonMain.cpp
  IostreamConnection.cpp
  IostreamStorageConnection.cpp
  main.cpp
  ../lib/TransmissionArduino/libraries/transmission-cpp/src/Pipe.cpp
  ../lib/TransmissionArduino/libraries/transmission-cpp/src/Pipe.h
)
target_link_libraries(ion-stdio ion-cpp)