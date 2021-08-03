
add_executable(Pico 
   src/main.cpp
   src/PicoApplication.cpp
)

target_link_libraries(Pico PRIVATE SpectralAnalysis CLI11::CLI11)

target_include_directories(Pico PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#target_compile_definitions(Plot PRIVATE PLOT_DEBUG)