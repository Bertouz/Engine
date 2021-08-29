
add_library(Monitoring STATIC
		monitoring.cpp
    )

target_include_directories(Monitoring PUBLIC
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
