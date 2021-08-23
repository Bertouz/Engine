
add_library(Monitoring INTERFACE
    )

target_include_directories(Monitoring INTERFACE
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
