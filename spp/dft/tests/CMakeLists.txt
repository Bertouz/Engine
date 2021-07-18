message(STATUS "Building Tests")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
add_subdirectory(unit)
if(ENABLE_MEMCHECK)
   add_custom_target(memcheck-lib1 ctest -R testu-lib1 -D ExperimentalMemCheck COMMENT "Target run unit test witch memcheck" WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif(ENABLE_MEMCHECK)
list(POP_BACK CMAKE_MESSAGE_INDENT)

