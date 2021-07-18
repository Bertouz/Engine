message(STATUS "Building Unit Tests")
list(APPEND CMAKE_MESSAGE_INDENT " ")

# Creating target for all unit tests
# I prefer to have one big executable with a filter parameter

add_executable(testu-app1
    main_testu.cpp
    hello-test.cpp
    )

target_link_libraries(testu-app1 PRIVATE Catch2::Catch2 app1)

# Add the target to the list of ctest's tests
add_test(testu-app1 testu-app1)

list(POP_BACK CMAKE_MESSAGE_INDENT)

