cmake_minimum_required(VERSION 3.14)
project(cleanpp_gtest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

link_directories(${CMAKE_SOURCE_DIR}/..)
include_directories(${CMAKE_SOURCE_DIR}/../include/cleanpp)

enable_testing()

include(GoogleTest)

# For each Test*.cpp file in cleanpp-gtest:
#     build an executable,
#     link libraries,
#     and tell googletest about it.
file( GLOB APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Test*.cpp )
foreach( sourcefile ${APP_SOURCES} )
  # extract the executable name from the source file name
  file( RELATIVE_PATH
    sourcefile_rel
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${sourcefile}
  )
  string( REPLACE
    ".cpp" 
    "" 
    execfile 
    ${sourcefile_rel}
  )

  # buid executable
  add_executable(
    ${execfile}
    ${sourcefile_rel}
  )

  # link libraries
  target_link_libraries(
    ${execfile}
    gtest_main
    Cleanpp
  )

  # tell googletest about it
  gtest_discover_tests(
    ${execfile}
  )
endforeach( sourcefile ${APP_SOURCES} )
