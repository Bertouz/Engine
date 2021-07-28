
add_executable(Pico 
   src/main.cpp
)

target_link_libraries(Pico PRIVATE Dft CLI11::CLI11)