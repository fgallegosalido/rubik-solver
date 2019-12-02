add_executable(rubik_test
    main.cpp
    unit_tests.cpp
)
target_link_libraries(rubik_test
    project_options
    project_warnings
    core
    CONAN_PKG::catch2
)

add_test(NAME rubik_test COMMAND rubik_test)
