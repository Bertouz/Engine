
add_executable(microbench main_microbenchmarks.cpp hello-bench.cpp)
target_link_libraries(microbench PRIVATE MyCppProject benchmark::benchmark)
target_compile_options(microbench PRIVATE -l pthread)
add_custom_target(mbench COMMAND microbench WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/benchmarks/micro COMMENT "Target to run micro benchmarks")
