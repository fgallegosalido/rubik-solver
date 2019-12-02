cmake_minimum_required(VERSION 3.12)
project(RubikSolver VERSION 0.0.1 LANGUAGES CXX)

find_program(CCACHE ccache)
if(CCACHE)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif()

# Link this 'library' to use the standard warnings
add_library(project_warnings INTERFACE)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE cxx_std_20)
target_include_directories(project_options INTERFACE include)

target_compile_options(project_warnings INTERFACE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wold-style-cast
    -Wcast-align
    -Wnon-virtual-dtor
    -Woverloaded-virtual
)


option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" OFF)
option(ENABLE_CPPCHECK "Enable testing with cppcheck" OFF)

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
    else()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()

if(ENABLE_CPPCHECK)
    find_program(CPPCHECK cppcheck)
    if(CPPCHECK)
        set(CMAKE_CXX_CPPCHECK ${CPPCHECK}
                --enable=warning,performance
                --inconclusive
                --force
                --inline-suppr)
    else()
        message(SEND_ERROR "cppcheck requested but executable not found")
    endif()
endif()

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS SKIP_STD)

# Builds utilities library
add_library(core
    source/utilities.cpp
    source/cube.cpp
)
target_link_libraries(core PRIVATE
    project_options
    project_warnings
)

add_library(partial_solvers
    source/old_pochmann_corners.cpp
    source/old_pochmann_edges.cpp
    source/m2_edges.cpp
    source/cross.cpp
)
target_link_libraries(partial_solvers PUBLIC
    project_options
    project_warnings
    core
)

# Builds the methods that solve the cube
add_library(solvers
    source/old_pochmann_solver.cpp
    source/old_pochmann_blind_solver.cpp
    source/old_pochmann_m2_solver.cpp
    source/old_pochmann_m2_blind_solver.cpp
)
target_link_libraries(solvers PUBLIC
    project_options
    project_warnings
    partial_solvers
)

# Builds the executables
add_executable(debug tests/debug.cpp)
target_link_libraries(debug PRIVATE
    project_options
    project_warnings
    core
    partial_solvers
    solvers
)

add_executable(main source/main.cpp)
target_link_libraries(main PRIVATE
    project_options
    project_warnings
    solvers
)

# Testing
option(BUILD_TESTS "Builds all the tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
