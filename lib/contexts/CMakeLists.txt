
add_library(Contexts STATIC
    strand.cpp
    task_utils.cpp
)

target_include_directories(Contexts PUBLIC
                       $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # for headers when building
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(Contexts PUBLIC pthread)

set_property(TARGET Contexts PROPERTY CXX_STANDARD 20)
