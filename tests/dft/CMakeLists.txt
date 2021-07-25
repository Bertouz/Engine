message(STATUS "Building Dft Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(testu-dft
    main_testu.cpp
    fftw3_wrapper-test.cpp
    )

target_link_libraries(testu-dft PRIVATE Catch2::Catch2 Dft )

set_property(TARGET testu-dft PROPERTY CXX_STANDARD 20)

add_test(testu-dft testu-dft)

list(POP_BACK CMAKE_MESSAGE_INDENT)

