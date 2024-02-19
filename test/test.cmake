# =====================================================
#  Public Domain: Inspired by github.com/KjellKod/g3log/CMakeLists.cmake
#  2015, April 30, @author Kjell.Hedstrom
# =====================================================

# ref: https://google.github.io/googletest/quickstart-cmake.html
include(FetchContent)
FetchContent_Declare(
   googletest
   URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB TEST_SRC_FILES "test/*.cpp")
set(TestRunner UnitTestRunner)
enable_testing()

message(" include directories: ${PROJECT_SRC} ${PROJECT_SRC}/../test")
enable_testing()
add_executable(${TestRunner}  ${TEST_SRC_FILES})
target_include_directories(${TestRunner}  PRIVATE 
   ${CMAKE_CURRENT_SOURCE_DIR}/src
   ${pugixml_SOURCE_DIR}/src)

target_link_libraries(
   ${TestRunner}  
   mazelib
   pugixml
   GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TestRunner} )