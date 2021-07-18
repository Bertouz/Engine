find_program(CLANG_TIDY_EXECUTABLE clang-tidy REQUIRED)
if(CLANG_TIDY_EXECUTABLE)
    message(STATUS "Found clang-tidy = ${CLANG_TIDY_EXECUTABLE}")
    file(GLOB_RECURSE SOURCE ${CMAKE_SOURCE_DIR}/*.cpp)
    add_custom_target(tidy ALL
    COMMAND ${CLANG_TIDY_EXECUTABLE} ${SOURCE}
    )
endif(CLANG_TIDY_EXECUTABLE)
