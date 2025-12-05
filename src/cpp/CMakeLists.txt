cmake_minimum_required(VERSION 3.31)
project(ion-cpp)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

# Compile ion-cpp library for local build machine architecture
set(ION_LIB_SOURCE_DIR ${ION}/src)
set(TRANSMISSION_LIB_SOURCE_DIR ${TRANSMISSION}/src)
include_directories(${ION_LIB_SOURCE_DIR} ${TRANSMISSION_LIB_SOURCE_DIR})
file(GLOB_RECURSE ION_FILES ${ION_LIB_SOURCE_DIR}/*.cpp ${TRANSMISSION_LIB_SOURCE_DIR}/*.cpp)
add_library(ion-cpp STATIC ${ION_FILES})

target_include_directories(ion-cpp PUBLIC
  ${ONDA}/src
  ${ION_LIB_SOURCE_DIR}
  ${TRANSMISSION_LIB_SOURCE_DIR}
)

target_link_libraries(ion-cpp PRIVATE
  onda
  transmission-cpp-lib
)

# ion-cpp-coverage is used by tests
add_library(ion-cpp-coverage STATIC ${ION_FILES})
target_include_directories(ion-cpp-coverage PUBLIC
  ${ONDA}/src
  ${ION_LIB_SOURCE_DIR}
  ${TRANSMISSION_LIB_SOURCE_DIR}
)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(ion-cpp-coverage PRIVATE --coverage -O0 -g)
  target_link_options(ion-cpp-coverage PRIVATE --coverage)
endif()

if(ENABLE_COVERAGE AND (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(ion-cpp PRIVATE --coverage -O0 -g)
  target_link_options(ion-cpp PRIVATE --coverage)
endif()