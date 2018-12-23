cmake_minimum_required(VERSION 3.12)
project(RubikSolver VERSION 0.0.1 LANGUAGES CXX)

# Link this 'library' to use the standard warnings
add_library(project_warnings INTERFACE)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE cxx_std_17)
target_include_directories(project_options INTERFACE include)

target_compile_options(project_warnings INTERFACE
                        -Wall
                        -Wextra
                        -Wpedantic
                        -Wshadow
                        -Wold-style-cast
                        -Wcast-align
                        -Wnon-virtual-dtor
                        -Woverloaded-virtual)


option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" FALSE)
option(ENABLE_CPPCHECK "Enable testing with cppcheck" FALSE)

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

# Builds utilities library
add_library(utilities source/utilities.cpp)
target_link_libraries(utilities PRIVATE project_options project_warnings)

# Builds the cube class
add_library(cube source/cube.cpp)
target_link_libraries(cube PRIVATE project_options project_warnings)

# Builds the methods that doesn't solve the cube
add_library(old_pochmann_corners source/old_pochmann_corners.cpp)
target_link_libraries(old_pochmann_corners PRIVATE project_options project_warnings
                        cube utilities)
add_library(old_pochmann_edges source/old_pochmann_edges.cpp)
target_link_libraries(old_pochmann_edges PRIVATE project_options project_warnings
                        cube utilities)
add_library(m2_edges source/m2_edges.cpp)
target_link_libraries(m2_edges PRIVATE project_options project_warnings
                        cube utilities)
add_library(cross source/cross.cpp)
target_link_libraries(cross PRIVATE project_options project_warnings
                        cube utilities)

# Builds the methods that solve the cube
add_library(old_pochmann_solver source/old_pochmann_solver.cpp)
target_link_libraries(old_pochmann_solver PRIVATE project_options project_warnings
                        old_pochmann_corners old_pochmann_edges)
add_library(old_pochmann_blind_solver source/old_pochmann_blind_solver.cpp)
target_link_libraries(old_pochmann_blind_solver PRIVATE project_options project_warnings
                        old_pochmann_solver)
add_library(old_pochmann_m2_solver source/old_pochmann_m2_solver.cpp)
target_link_libraries(old_pochmann_m2_solver PRIVATE project_options project_warnings
                        old_pochmann_corners m2_edges)
add_library(old_pochmann_m2_blind_solver source/old_pochmann_m2_blind_solver.cpp)
target_link_libraries(old_pochmann_m2_blind_solver PRIVATE project_options project_warnings
                        old_pochmann_m2_solver)

# Builds the executables
add_executable(debug tests/debug.cpp)
target_link_libraries(debug PRIVATE project_options project_warnings
                        cube utilities)

add_executable(main source/main.cpp)
target_link_libraries(main PRIVATE project_options project_warnings
                        old_pochmann_solver
                        old_pochmann_blind_solver
                        old_pochmann_m2_solver
                        old_pochmann_m2_blind_solver)
