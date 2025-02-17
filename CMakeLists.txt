cmake_minimum_required(VERSION 3.0.0)

# Setup project
project(LwLibPROJECT)

# -------------------------------------------------
# This CMakeLists.txt is used only if it is a top-level file.
# Purpose of it is to be able to compile project in standalone way only
#
# When library sources are to be included in another project
# user shall use /lwmem/CMakeLists.txt instead
if (NOT PROJECT_IS_TOP_LEVEL)
    message(FATAL_ERROR "This CMakeLists.txt can only be used as top-level. Use /lwmem/CMakeLists.txt for library include purpose")
endif()

# Set as executable
add_executable(${PROJECT_NAME})

# Add key executable block
target_sources(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/dev/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/tests/lwmem_test.c

    # posix port
    ${CMAKE_CURRENT_LIST_DIR}/lwmem/src/system/lwmem_sys_posix.c
    )

# Add key include paths
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/dev
    )

# Compilation definition information
target_compile_definitions(${PROJECT_NAME} PUBLIC
    WIN32
    _DEBUG
    CONSOLE
    LWMEM_DEV
    )

# Compiler and linker options
target_compile_options(${PROJECT_NAME} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    )

# Add subdir with lwmem and link to the project
add_subdirectory("lwmem")
target_link_libraries(${PROJECT_NAME} lwmem)
target_link_libraries(${PROJECT_NAME} lwmem_cpp)

# Add POSIX pthread lib
target_link_libraries(${PROJECT_NAME} pthread)