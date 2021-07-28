message(STATUS "Building spectral analysis examples")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(example-periodogram
    periodogram-example.cpp
)

target_link_libraries(example-periodogram PRIVATE SpectralAnalysis Plot)

target_compile_options(example-periodogram PRIVATE -l pthread)

set_target_properties(example-periodogram PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/examples" CXX_STANDARD 20)

list(POP_BACK CMAKE_MESSAGE_INDENT)
