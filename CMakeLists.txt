cmake_minimum_required(VERSION 3.10)

project(ChannelMap VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

file(GLOB SOURCES "src/*.cc")
file(GLOB HEADERS "include/*.hh")

### main library
add_library(ChannelMap SHARED ${SOURCES})
target_include_directories(ChannelMap PUBLIC include)
target_include_directories(ChannelMap PRIVATE)

### for debug
add_definitions(-DDEBUG)

### for test
add_executable(test_program test.cc)
target_compile_features(test_program PRIVATE cxx_std_20)
target_link_libraries(test_program PRIVATE ChannelMap)

### install
install(TARGETS test_program DESTINATION bin)
install(TARGETS ChannelMap DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
