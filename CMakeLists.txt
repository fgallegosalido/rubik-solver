cmake_minimum_required(VERSION 3.10)
project(RubikSolver VERSION 0.0.1 LANGUAGES CXX)

# Link this 'library' to use the standard warnings
add_library(project_warnings INTERFACE)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)

target_compile_features(project_options INTERFACE cxx_std_17)
target_include_directories(project_options INTERFACE include)

target_compile_options(project_warnings INTERFACE -Wall -Wextra -Wpedantic -Wshadow)


option(ENABLE_CLANG_TIDY "Enable testing with clang-tidy" FALSE)

if(ENABLE_CLANG_TIDY)
  find_program(CLANGTIDY clang-tidy)
  if(CLANGTIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANGTIDY})
  else()
    message(SEND_ERROR "clang-tidy requested but executable not found")
  endif()
endif()

add_library(cube source/cube.cpp)
target_link_libraries(cube PRIVATE project_options project_warnings)

add_executable(debug tests/debug.cpp)
target_link_libraries(debug PRIVATE project_options project_warnings cube)
