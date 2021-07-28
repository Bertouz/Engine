
message(STATUS "Building spectral analysis Unit Tests")

list(APPEND CMAKE_MESSAGE_INDENT " ")

add_executable(testu-spectral-analysis
    main.cpp
    test-periodogram.cpp
    )

target_link_libraries(testu-spectral-analysis PRIVATE Catch2::Catch2 SpectralAnalysis Plot)

set_property(TARGET testu-spectral-analysis PROPERTY CXX_STANDARD 20)

add_test(testu-spectral-analysis testu-spectral-analysis)

list(POP_BACK CMAKE_MESSAGE_INDENT)
