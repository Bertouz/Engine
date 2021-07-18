find_program(CLANG_FORMAT_EXECUTABLE clang-format REQUIRED)
if(CLANG_FORMAT_EXECUTABLE)
    message(STATUS "Found clang-format = ${CLANG_FORMAT_EXECUTABLE}")
    file(GLOB_RECURSE SOURCE ${CMAKE_SOURCE_DIR}/*.cpp)
    add_custom_target(format
    COMMAND ${CLANG_FORMAT_EXECUTABLE} -i ${SOURCE}
    )
endif(CLANG_FORMAT_EXECUTABLE)
