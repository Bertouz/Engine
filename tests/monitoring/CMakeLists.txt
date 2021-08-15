message(STATUS "Building Monitoring Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(testu-monitoring
    main.cpp
    task_decorator-test.cpp
    )

target_link_libraries(testu-monitoring PRIVATE Catch2::Catch2 Monitoring )

set_property(TARGET testu-monitoring PROPERTY CXX_STANDARD 20)

add_test(testu-monitoring testu-monitoring)

list(POP_BACK CMAKE_MESSAGE_INDENT)
