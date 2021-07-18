
add_executable(pico 
   src/main.cpp
)

target_link_libraries(pico PRIVATE dft CLI11::CLI11)