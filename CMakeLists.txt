# CMakeLists.txt for a C++23 modules project using EXPERIMENTAL std module support on GCC

# Require a recent CMake version. 4.1.2 is required.
cmake_minimum_required(VERSION 4.1)

# --- Enable Experimental std Module Support ---
# This is the master switch that enables the feature via a version-specific UUID.
# WARNING: This UUID will change in future CMake versions, breaking this script.
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")

# Define the project and enable the C++ language.
project(RenderCSV LANGUAGES CXX)

# --- Main Program Target Definition ---
file(GLOB_RECURSE SOURCE_FILES "*.cpp")
file(GLOB_RECURSE INTERFACE_FILES "*.cppm")

# 1. Define the executable with its "normal" sources (main + implementations).
add_executable(render_csv ${SOURCE_FILES})

# 2. Declare the module INTERFACE files for the target.
target_sources(render_csv PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
        ${INTERFACE_FILES}
)

# 3. Set the C++ standard for the target.
target_compile_features(render_csv PUBLIC cxx_std_23)

# 4. For the target, explicitly enable std module dependency scanning.
# This works in conjunction with the master experimental switch.
set_property(TARGET render_csv PROPERTY CXX_MODULE_STD ON)

# --- Compiler-Specific Checks & Common Settings ---

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 15)
    message(FATAL_ERROR "GCC version 15 or newer is required for this project.")
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_link_libraries(render_csv stdc++exp)
endif()

# Organize output directories.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")