cmake_minimum_required(VERSION 3.8)

set(This ImGUI)

set(HEADERS 
    include/imconfig.h
    include/imgui_internal.h
    include/imgui.h
    include/imstb_rectpack.h
    include/imstb_textedit.h
    include/imstb_truetype.h
)

set(SOURCES
    src/imgui_demo.cpp
    src/imgui_draw.cpp
    src/imgui_widgets.cpp
    src/imgui.cpp
)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${This} PUBLIC include)

set_target_properties(${This} PROPERTIES 
    FOLDER Libraries
)