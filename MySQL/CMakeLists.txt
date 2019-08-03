cmake_minimum_required(VERSION 3.8)

set(This MySQL)

set(HEADERS 
    include/MySQL/MySQL.hpp
)

set(SOURCES 
    src/MySQL.cpp
)

# -------------------------------------------
# How to add a directory to include path: 
# include_directories(${variable}/include)
# -------------------------------------------
# Boost:
include_directories(${boost}/include)
# MySQL:
include_directories(${mysql_connector}/include/jdbc)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

# target_link_libraries(${This} PUBLIC 
#    
# )

target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Libraries
)