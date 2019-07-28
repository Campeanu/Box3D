cmake_minimum_required(VERSION 3.8)

set(This Box3DTests)

set(SOURCES 
    src/Box3DTests.cpp
)

add_executable(${This} ${Sources})

set_target_properties(${This} PROPERTIES 
    FOLDER Tests
)