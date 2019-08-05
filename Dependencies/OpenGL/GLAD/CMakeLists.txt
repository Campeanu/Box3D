cmake_minimum_required(VERSION 3.8)

set(This GLAD)

set(HEADERS 
    include/glad/glad.h
    include/KHR/khrplatform.h
)

set(SOURCES 
    src/glad.c
)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Libraries
)