message(STATUS "Building lib1")

list(APPEND CMAKE_MESSAGE_INDENT "  ")

target_sources(lib1 PRIVATE hello.cpp)

list(POP_BACK CMAKE_MESSAGE_INDENT)
