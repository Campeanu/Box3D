cmake_minimum_required(VERSION 3.8)

set(This SandboxTests)

set(SOURCES 
    src/SandboxTests.cpp
)

add_executable(${This} ${Sources})

set_target_properties(${This} PROPERTIES 
    FOLDER Tests
)