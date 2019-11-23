cmake_minimum_required(VERSION 3.0)

project (WordLadder)
enable_testing()
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
include_directories(include)

set(LIBRARY_NAME wordladder)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib CACHE PATH "Where to place compiled static libraries.")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib CACHE PATH "Where to place compiled shared libraries.")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin CACHE PATH "Where to place compiled executables.")

#################################
#       library
#################################
file(GLOB LIBSOURCES "src/word_ladder*.cpp")

# this is the "object library" target: compiles the sources only once
add_library(objlib OBJECT ${LIBSOURCES})

# shared libraries need PIC
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

# shared and static libraries built from the same object files
add_library(${LIBRARY_NAME}        SHARED $<TARGET_OBJECTS:objlib>)
add_library(${LIBRARY_NAME}_static STATIC $<TARGET_OBJECTS:objlib>)

# Set the location for library installation -- i.e., /usr/lib in this case
# not really necessary in this example. Use "sudo make install" to apply
install(TARGETS ${LIBRARY_NAME} DESTINATION /usr/lib)

#################################
#       application
#################################
add_executable(wordladderapp src/wordladderapp.cpp)
target_link_libraries(wordladderapp ${LIBRARY_NAME}_static)

#################################
#       tests
#################################
add_executable(test_word_ladder test/test_word_ladder.cpp)
target_link_libraries(test_word_ladder ${LIBRARY_NAME}_static ${Boost_LIBRARIES})

add_test(test_word_ladder ../bin/test_word_ladder)
