

add_executable(DummyProcess
   src/main.cpp
)

target_link_libraries(DummyProcess PRIVATE CLI11::CLI11 pthread)
