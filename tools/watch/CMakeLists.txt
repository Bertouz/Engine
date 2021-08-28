
add_executable(Watch
   src/main.cpp
)

target_link_libraries(Watch PRIVATE CLI11::CLI11 Plot Monitoring)

target_include_directories(Watch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
