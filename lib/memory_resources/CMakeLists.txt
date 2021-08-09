add_library(MemoryResources INTERFACE
)

target_include_directories(MemoryResources INTERFACE
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
