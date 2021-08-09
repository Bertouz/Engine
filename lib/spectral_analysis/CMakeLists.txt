

# SpectralAnalysis lib
add_library(SpectralAnalysis INTERFACE)
target_link_libraries(SpectralAnalysis INTERFACE Dft)
target_include_directories(SpectralAnalysis INTERFACE
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
