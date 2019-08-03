cmake_minimum_required(VERSION 3.8)
set(This Box3D)

# Set project name.
project(${This} C CXX)

# Set the standard.
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD 17)

# This variable is used to initialize the POSITION_INDEPENDENT_CODE property on all the targets.
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Enables testing for this directory and below. 
enable_testing()

# Store a property of directory scope in the named variable.
get_directory_property(ParentDirectory PARENT_DIRECTORY)
if(ParentDirectory STREQUAL "")

    if(MSVC)
        option(RUNTIME_STATIC_LINKAGE "Link with runtime library statically" OFF)
    endif(MSVC)

    if(MSVC AND RUNTIME_STATIC_LINKAGE)
        foreach(flag
            CMAKE_C_FLAGS
            CMAKE_CXX_FLAGS
            CMAKE_C_FLAGS_DEBUG
            CMAKE_CXX_FLAGS_DEBUG
            CMAKE_C_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_RELEASE
            CMAKE_C_FLAGS_MINSIZEREL
            CMAKE_CXX_FLAGS_MINSIZEREL
            CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_RELWITHDEBINFO
        )
            if(${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif(${flag} MATCHES "/MD")
        endforeach(flag)
    endif(MSVC AND RUNTIME_STATIC_LINKAGE)

    # Keep Google Test's linkage of the runtime in sync with our own.
    if(MSVC)
        if(RUNTIME_STATIC_LINKAGE)
            set(gtest_force_shared_crt OFF CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib." FORCE)
        else(RUNTIME_STATIC_LINKAGE)
            set(gtest_force_shared_crt ON  CACHE BOOL "Use shared (DLL) run-time lib even when Google Test is built as static lib." FORCE)
        endif(RUNTIME_STATIC_LINKAGE)
    endif(MSVC)

    # Organize applications, libraries, etc. in folders in the IDE.
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Ensure proper loading of side-loaded shared libraries on all targets.
    set(CMAKE_SKIP_BUILD_RPATH FALSE)
    set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    if(APPLE)
        set(CMAKE_INSTALL_RPATH "@loader_path")
    elseif(UNIX)
        set(CMAKE_INSTALL_RPATH "\$ORIGIN")
    endif()

    # Don't add "d" postfix for debug builds of libraries.
    set(CMAKE_DEBUG_POSTFIX "")

    # Suppress Microsoft warnings about functions being unsafe.
    add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS)    
    
    # Google Test
    set(BUILD_GTEST ON  CACHE BOOL "Builds the googletest subproject" FORCE)
    set(BUILD_GMOCK OFF CACHE BOOL "Builds the googlemock subproject" FORCE)
    add_subdirectory(Dependencies/googletest)
    set_target_properties(gtest gtest_main PROPERTIES
        FOLDER Libraries/googletest
    )

    # set(JSON_BuildTests OFF CACHE INTERNAL "")
    # add_subdirectory(Dependencies/json)
    #set_target_properties(nlohmann_json PROPERTIES
    #    FOLDER Libraries
    #)

    # Specify where to find external libraries.
    # Example:
    # set(Library "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Library")
    set(boost ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/boost)
    set(mysql_connector ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/mysql_connector)

endif(ParentDirectory STREQUAL "")
# Add subdirectories directly in this repository.
# Box3D:
add_subdirectory(Box3D)
# MySQL:
add_subdirectory(MySQL)
# Sandbox:
add_subdirectory(Sandbox)
# LoginSystem:
add_subdirectory(LoginSystem)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})