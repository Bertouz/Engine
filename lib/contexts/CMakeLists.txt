
add_library(Contexts INTERFACE
)

target_include_directories(Contexts INTERFACE
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(Contexts INTERFACE pthread)
set_property(TARGET Contexts PROPERTY CXX_STANDARD 20)
