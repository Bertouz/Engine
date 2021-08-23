message(STATUS "Building Contexts Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(testu-contexts
    main.cpp
    strand-test.cpp
    task_utils-test.cpp
    )

target_link_libraries(testu-contexts PRIVATE Catch2::Catch2 Contexts)

set_property(TARGET testu-contexts PROPERTY CXX_STANDARD 20)

add_test(testu-contexts testu-contexts)

list(POP_BACK CMAKE_MESSAGE_INDENT)
