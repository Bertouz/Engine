
add_library(ExecutionContext INTERFACE
)

target_include_directories(ExecutionContext INTERFACE
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

