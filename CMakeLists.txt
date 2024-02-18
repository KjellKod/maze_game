#  Build instructions:
#  --------------------
#  From directory cpp/build
#  linux: cmake ..; make
#  windows: cmake -G "Visual Studio 11" ..
#           msbuild maze.sln

cmake_minimum_required(VERSION 2.8)
project(maze)

if(UNIX)
   set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Werror -Wunused  ${CMAKE_CXX_FLAGS_DEBUG} -pthread")
endif()


# GTEST
INCLUDE(test/test.cmake)
enable_testing(true)


# pugixml
set(PUGIXML_ROOT 3rdParty/pugixml-1.14/src)
set(PUGIXML_HEADERS ${PUGIXML_ROOT}/pugixml.hpp ${PUGIXML_ROOT}/pugiconfig.hpp)
set(PUGIXML_SOURCES ${PUGIXML_HEADERS} ${PUGIXML_ROOT}/pugixml.cpp)
add_library(pugixml STATIC ${PUGIXML_SOURCES})
include_directories(${PUGIXML_ROOT})


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
include_directories(src)



set(TEST_SRC  test/test_main.cpp
              test/test_node.cpp
              test/test_graph.cpp
              test/test_pugixml_disabled.cpp
              test/test_scenario_0.cpp
              test/test_scenario_1.cpp
              test/map.xml.impl
              test/test_world_explorer.cpp)

add_executable(maze    ${SRC_MAIN} ${SRC_FILES} ${HEADER_FILES})
target_link_libraries(maze  pugixml)

