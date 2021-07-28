message(STATUS "Building Dft Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(testu-parser
    main.cpp
    csv-test.cpp
    )

target_link_libraries(testu-parser PRIVATE Catch2::Catch2)

target_include_directories(testu-parser PRIVATE ${CMAKE_SOURCE_DIR}/include)

set_property(TARGET testu-parser PROPERTY CXX_STANDARD 20)

add_test(testu-parser testu-parser)

target_compile_definitions(testu-parser INTERFACE TESTDATA_DIR="${CMAKE_SOURCE_DIR}/tests/test_data")

list(POP_BACK CMAKE_MESSAGE_INDENT)
