add_library(plot INTERFACE)

set(plot_deps "")

if(USE_SCIPLOT)
   list(APPEND plot_deps sciplot)
endif(USE_SCIPLOT)

if(plot_deps)
    target_link_libraries(plot INTERFACE sciplot)
endif()

target_include_directories(plot INTERFACE include/)

target_compile_definitions(plot INTERFACE SCIPLOT)
