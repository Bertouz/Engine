message(STATUS "Building ${curr_subproject} Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

set(test_name "testu-${curr_subproject}")

add_executable(${test_name}
    main_testu.cpp
    fftw3_wrapper-test.cpp
    )

target_link_libraries(${test_name} PRIVATE 
    Catch2::Catch2 
    ${curr_subproject}
    plot
)
set_property(TARGET ${test_name} PROPERTY CXX_STANDARD 20)

# Add the target to the list of ctest's tests
add_test(${test_name} ${test_name})

list(POP_BACK CMAKE_MESSAGE_INDENT)

