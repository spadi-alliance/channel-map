cmake_minimum_required(VERSION 3.10)

project(ChannelMap VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

### main library
add_library(ChannelMap SHARED ${SOURCES})
target_include_directories(ChannelMap PUBLIC include)
target_include_directories(ChannelMap PRIVATE)

### for debug
# add_definitions(-DDEBUG)

### for skeleton
add_executable(skeleton_program skeleton.cpp)
target_compile_features(skeleton_program PRIVATE cxx_std_17)
target_link_libraries(skeleton_program PRIVATE ChannelMap)

### install
install(TARGETS skeleton_program DESTINATION bin)
install(TARGETS ChannelMap DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
