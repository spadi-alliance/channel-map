cmake_minimum_required(VERSION 3.10)

project(channel-map VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
set(CMAKE_BUILD_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

### main library
add_library(channel-map SHARED ${SOURCES})
target_include_directories(channel-map PUBLIC include)
target_include_directories(channel-map PRIVATE)

### script
set(SCRIPT_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/script/channel-map-config)

### debug
# add_definitions(-DDEBUG)

### skeleton
add_executable(skeleton-program skeleton.cpp)
target_compile_features(skeleton-program PRIVATE cxx_std_17)
target_link_libraries(skeleton-program PRIVATE channel-map stdc++fs)

### install
install(TARGETS skeleton-program DESTINATION bin)
install(TARGETS channel-map DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
install(FILES ${SCRIPT_SOURCE} DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
	GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
