message(STATUS "Building App1")

list(APPEND CMAKE_MESSAGE_INDENT "  ")

target_sources(app1 PRIVATE hello.cpp)

list(POP_BACK CMAKE_MESSAGE_INDENT)
