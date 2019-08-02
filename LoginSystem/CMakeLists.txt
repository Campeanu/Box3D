cmake_minimum_required(VERSION 3.8)

set(This LoginSystem)

set(HEADERS 
    include/LoginSystem/Login.hpp
)

set(SOURCES 
    src/Login.cpp
)

include_directories(${boost}/include)
# MySQL:
include_directories(${mysql_connector}/include/jdbc)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${This} PUBLIC 
    nlohmann_json::nlohmann_json
    MySQL
)

target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Libraries
)

# add_subdirectory(test)