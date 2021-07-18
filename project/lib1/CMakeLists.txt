

#############################
### lib1
#############################
add_library(lib1 SHARED "" )

add_subdirectory(src)

target_include_directories(lib1 PUBLIC
                       $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#target_link_libraries()

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
    include(CTest)
    add_subdirectory(tests)
endif(BUILD_TESTS)

#############################
### Installation
#############################

#Install includes 
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ FILES_MATCHING PATTERN *.h*)
