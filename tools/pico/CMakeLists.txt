
add_executable(Pico 
   src/main.cpp
   src/PicoApplication.cpp
)

target_link_libraries(Pico PRIVATE SpectralAnalysis CLI11::CLI11 Plot)

target_include_directories(Pico PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)