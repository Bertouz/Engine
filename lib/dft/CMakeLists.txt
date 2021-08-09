

#############################
### DFT
#############################

add_library(Dft ${SHARED_OR_STATIC}
    "fftw3/fftw3_wrapper.cpp" 
)

target_include_directories(Dft PUBLIC
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(Dft PUBLIC FFTW3::fftw3 INTERFACE Complex)
