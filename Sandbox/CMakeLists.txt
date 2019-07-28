cmake_minimum_required(VERSION 3.8)

set(This Sandbox)

# set(HEADERS 
#     include/Sandbox/
# )

set(SOURCES
    src/Sandbox.cpp
)

# -------------------------------------------
# How to add a directory to include path: 
# include_directories(${variable}/include)

# How to add a directory to link path: 
# link_directories(${variable}/lib)
# -------------------------------------------

# How to add compilation definitions:
# add_compile_definitions(difinition)
# add_compile_definitions(GLEW_STATIC)

# How to set an output path for an executable file  
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# library
# add_library(${This} STATIC ${SOURCES} ${HEADERS})
add_executable(${This} ${SOURCES})

# ---------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------
# ------------------------------------------------ PRIVATE ------------------------------------------------
target_link_libraries(${This} PRIVATE
    Box3D
#   nlohmann_json::nlohmann_json
#   GLAD
#   ImGUI
#   GLEW
#   glfw
#   opengl32
)

# ---------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------
# ------------------------------------------------ PRIVATE ------------------------------------------------
target_include_directories(${This} PRIVATE include)

set_target_properties(${This} PROPERTIES 
    FOLDER Applications
)

# add_subdirectory(test)