
message(STATUS "Building ${curr_subproject} Benchmarks")

list(APPEND CMAKE_MESSAGE_INDENT " ")

set(bench_name "bench-${curr_subproject}")

add_executable(${bench_name} main.cpp hello-bench.cpp)

target_link_libraries(${bench_name} PRIVATE ${curr_subproject} benchmark::benchmark)

target_compile_options(${bench_name} PRIVATE -l pthread)

set_target_properties(${bench_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/benchmarks")

list(POP_BACK CMAKE_MESSAGE_INDENT)
