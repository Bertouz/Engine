

#############################
### lib1
#############################
set(curr_subproject dft)

add_library(${curr_subproject} ${SHARED_OR_STATIC}
    "src/fftw3/fftw3_wrapper.cpp" 
)

target_include_directories(${curr_subproject} PUBLIC
                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${curr_subproject} PRIVATE FFTW3::fftw3)

#############################
### benchmarks
#############################
if(ENABLE_MICRO_BENCHMARKS)
   add_subdirectory(benchmarks/micro)
endif(ENABLE_MICRO_BENCHMARKS)

#############################
### Tests
#############################
if(BUILD_TESTS)
    add_subdirectory(tests)
endif(BUILD_TESTS)

#############################
### Installation
#############################

#Install includes 
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ FILES_MATCHING PATTERN *.h*)
