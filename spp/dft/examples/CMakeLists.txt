message(STATUS "Building ${curr_subproject} examples")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(fftw3_wrapper-example
    fftw3_wrapper-example.cpp
)

target_link_libraries(fftw3_wrapper-example PRIVATE ${curr_subproject} plot)

target_compile_options(fftw3_wrapper-example PRIVATE -l pthread)

set_target_properties(fftw3_wrapper-example PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples" CXX_STANDARD 20)

list(POP_BACK CMAKE_MESSAGE_INDENT)
