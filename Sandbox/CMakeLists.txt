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
# -------------------------------------------
# Boost:
include_directories(${boost}/include)
# MySQL:
include_directories(${mysql_connector}/include/jdbc)


# -------------------------------------------
# How to add a directory to link path: 
# link_directories(${variable}/lib)
# -------------------------------------------
link_directories(${mysql_connector}/lib64/vs14)

# How to add compilation definitions:
# add_compile_definitions(difinition)
# Example
# add_compile_definitions(GLEW_STATIC)
add_compile_definitions(BOX3D_PLATFORM_WINDOW)
add_compile_definitions(BOX3D_DEBUG)
add_compile_definitions(GLEW_STATIC)
add_compile_definitions(GLFW_INCLUDE_NONE)
add_compile_definitions(IMGUI_IMPL_OPENGL_LOADER_GLAD)

# Specify platform: 
#   * BOX3D_PLATFORM_WINDOW
#   * BOX3D_PLATFORM_MACOSX
#   * BOX3D_PLATFORM_LINUX
add_compile_definitions(BOX3D_PLATFORM_WINDOW)

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
    mysqlcppconn
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