cmake_minimum_required(VERSION 3.10)
 
set(TARGET_APP server)
 
# set the project name and version
project(${TARGET_APP}
        VERSION 1.0)
        

# boost
find_package(Boost 1.82.0 REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})
# server_core
find_library(servercore_LIBRARIES NAMES libserver_core.a PATHS ../servercore/build)
include_directories(../servercore/include)

# find source and header
file(GLOB_RECURSE HEADERS
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)

file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# make exe file
add_executable(${TARGET_APP} 
               ${SOURCES})

# link libraries
target_link_libraries(${TARGET_APP} ${Boost_LIBRARIES})
target_link_libraries(${TARGET_APP} ${servercore_LIBRARIES})

message("HAHAH " ${CMAKE_CURRENT_SOURCE_DIR})

# compile option for c17
target_compile_features(${TARGET_APP} PRIVATE cxx_std_17)