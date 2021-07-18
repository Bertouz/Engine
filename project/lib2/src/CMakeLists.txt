message(STATUS "Building lib2")

list(APPEND CMAKE_MESSAGE_INDENT "  ")

target_sources(lib2 PRIVATE hello.cpp)

list(POP_BACK CMAKE_MESSAGE_INDENT)
