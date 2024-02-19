#  Build instructions:
#  --------------------
#  From directory cpp/build
#  linux: cmake ..; make
#  run tests with one of [./UnitTestRunner || make test || ctest -V]

cmake_minimum_required(VERSION 3.21)
project(maze)


include(FetchContent)
FetchContent_Declare( 
  pugixml
  URL https://github.com/zeux/pugixml/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(pugixml)
set(PUGIXML_INCLUDE_DIR ${pugixml_SOURCE_DIR}/src)

if(UNIX)
   set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wunused  ${CMAKE_CXX_FLAGS_DEBUG} -pthread")
endif()

set(SRC_MAIN       src/main.cpp)
set(SRC_FILES      src/graph.cpp
                   src/node.cpp
                   src/world_explorer.cpp
                   src/parse_scenario.cpp
                   src/parse_map.cpp
                   src/string_utility.cpp)

set(HEADER_FILES   src/graph.hpp
                   src/node.hpp
                   src/world_explorer.hpp
                   src/parse_scenario.hpp
                   src/parse_map.hpp
                   src/string_utility.hpp)

message("SRC_FILES: ${SRC_FILES}")
message("SRC_MAIN: ${SRC_MAIN}")
add_library(mazelib SHARED ${SRC_FILES})
target_link_libraries(mazelib PRIVATE pugixml)
target_include_directories(mazelib PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
set_target_properties(mazelib PROPERTIES MACOSX_RPATH TRUE)

# GTEST
INCLUDE(test/test.cmake)
enable_testing(true)

add_executable(maze  ${SRC_MAIN})
target_include_directories(maze PRIVATE ${pugixml_SOURCE_DIR}/src)
target_link_libraries(maze PRIVATE mazelib pugixml)

