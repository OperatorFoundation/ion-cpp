cmake_minimum_required(VERSION 3.31)
project(ion-cpp-tests)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(CTEST_PROJECT_NAME ion-cpp)
set(CTEST_NIGHTLY_START_TIME 01:00:00 UTC)
set(CTEST_SUBMIT_URL https://my.cdash.org/submit.php?project=ion-cpp)
set(CTEST_DROP_SITE_CDASH TRUE)

# Set FetchContent to be quieter and show progress
set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.0
  GIT_SHALLOW TRUE  # Only fetch the specific tag, not full history
  GIT_PROGRESS TRUE # Show download progress
)

message(STATUS "Fetching Catch2...")
FetchContent_MakeAvailable(Catch2)

set(ION_CPP_LIB_TEST_DIR ${CMAKE_SOURCE_DIR}/tests)
set(ION_LIB_SOURCE_DIR ${ION}/src)
set(TRANSMISSION_LIB_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libraries/transmission-cpp/src)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

include_directories(${ION_LIB_SOURCE_DIR} ${TRANSMISSION_LIB_SOURCE_DIR} ${ONDA}/src)

add_executable(tests main.cpp
  squeeze_tests/int_tests.cpp
  squeeze_tests/float_tests.cpp
)

# Use the coverage version of the library for tests
target_link_libraries(tests PRIVATE ion-cpp-coverage onda Catch2::Catch2WithMain)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(tests PRIVATE --coverage -O0 -g)
  target_link_options(tests PRIVATE --coverage)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

  find_program(GCOV_PATH gcov)
  find_program(LCOV_PATH lcov)
  find_program(GENHTML_PATH genhtml)

  if(LCOV_PATH AND GCOV_PATH AND GENHTML_PATH)
    add_custom_target(coverage
      COMMAND ${LCOV_PATH} --directory . --zerocounters
      COMMAND tests
      COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
      COMMAND ${LCOV_PATH} --extract coverage.info
      '${CMAKE_SOURCE_DIR}/libraries/ion-cpp/*'
      --output-file coverage.filtered.info
      COMMAND ${GENHTML_PATH} coverage.filtered.info --output-directory coverage_html
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Generating coverage report"
    )
  else()
    # Fallback to gcov directly
    add_custom_target(coverage
      COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
      COMMAND ${CMAKE_COMMAND} -E make_directory coverage
      COMMAND tests
      COMMAND ${CMAKE_COMMAND} -E chdir coverage ${GCOV_PATH} -abcfu ${CMAKE_SOURCE_DIR}/src/*.cpp
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running gcov"
    )
  endif()
endif()