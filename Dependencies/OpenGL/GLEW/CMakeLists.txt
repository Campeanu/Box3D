cmake_minimum_required(VERSION 3.8)

set(This GLEW)

set(HEADERS 
    include/GL/eglew.h
    include/GL/glew.h
    include/GL/glxew.h
    include/GL/wglew.h
)

set(SOURCES 
    src/glew.c
    src/glewinfo.c
    src/visualinfo.c
)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Libraries
)