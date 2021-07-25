message(STATUS "Building Dft examples")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(example-fftw3_wrapper
    fftw3_wrapper-example.cpp
)

target_link_libraries(example-fftw3_wrapper PRIVATE Dft Plot)

target_compile_options(example-fftw3_wrapper PRIVATE -l pthread)

set_target_properties(example-fftw3_wrapper PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples" CXX_STANDARD 20)

list(POP_BACK CMAKE_MESSAGE_INDENT)
