cmake_minimum_required(VERSION 3.16)
 
set(TARGET_APP server)

set(HEADER_FILES 
    include/connector.hpp
    include/listner.hpp
    include/message.hpp
    include/servercore.hpp
    include/pch.hpp
    include/session.hpp
    include/tsqueue.hpp)
 
# set the project name and version
project(${TARGET_APP}
        VERSION 1.0)

include_directories(include)

find_package(Boost 1.82.0 REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})

add_library(${TARGET_APP} 
            src/connector.cpp
            src/listner.cpp
            src/session.cpp
            src/connector.cpp
            ${HEADER_FILES})

target_link_libraries(${TARGET_APP} ${Boost_LIBRARIES})

target_precompile_headers(${TARGET_APP} PRIVATE include/pch.hpp)