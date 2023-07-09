cmake_minimum_required(VERSION 3.8.2)
 
set(TARGET_APP server_core)

project(${TARGET_APP})

include_directories(include)

# find boost packages
find_package(Boost 1.82.0 REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})

# source
file(GLOB_RECURSE HEADERS
     ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)

file(GLOB_RECURSE SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${TARGET_APP} STATIC 
            ${SOURCES}
)

target_link_libraries(${TARGET_APP} ${Boost_LIBRARIES})
target_compile_features(${TARGET_APP} PRIVATE cxx_std_17)

