
add_library(Plot INTERFACE)

target_include_directories(Plot INTERFACE 
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(Plot INTERFACE 
                       $<BUILD_INTERFACE:sciplot> # for headers when building
                       $<INSTALL_INTERFACE:sciplot::sciplot>)

target_compile_definitions(Plot INTERFACE SCIPLOT)
