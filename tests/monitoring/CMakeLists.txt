message(STATUS "Building Monitoring Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(testu-monitoring
    main.cpp
    monitoring-test.cpp
    monitoring_data_parser-test.cpp

    )

target_link_libraries(testu-monitoring PRIVATE Catch2::Catch2 Monitoring Contexts)

set_property(TARGET testu-monitoring PROPERTY CXX_STANDARD 20)

add_test(testu-monitoring testu-monitoring)

list(POP_BACK CMAKE_MESSAGE_INDENT)
