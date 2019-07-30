cmake_minimum_required(VERSION 3.8)

set(This MySQLTests)

set(SOURCES 
    src/MySQLTests.cpp
)

add_executable(${This} ${Sources})

set_target_properties(${This} PROPERTIES 
    FOLDER Tests
)