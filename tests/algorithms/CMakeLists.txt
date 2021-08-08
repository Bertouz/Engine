message(STATUS "Building Algorithms Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(testu-algorithms
    main.cpp
    generation-test.cpp
    test-normalize.cpp
    test-integration.cpp
    )

target_link_libraries(testu-algorithms PRIVATE Catch2::Catch2 Plot)

target_include_directories(testu-algorithms PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_property(TARGET testu-algorithms PROPERTY CXX_STANDARD 20)

add_test(testu-algorithms testu-algorithms)

list(POP_BACK CMAKE_MESSAGE_INDENT)

