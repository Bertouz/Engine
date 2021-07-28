
message(STATUS "Building Dft Benchmarks")

list(APPEND CMAKE_MESSAGE_INDENT " ")


add_executable(bench-dft
main.cpp 
fftw3-bench.cpp
)

target_link_libraries(bench-dft PRIVATE Dft benchmark::benchmark)

target_compile_options(bench-dft PRIVATE -l pthread)

set_target_properties(bench-dft PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/benchmarks")

list(POP_BACK CMAKE_MESSAGE_INDENT)
