message(STATUS "Building Documentation")
list(APPEND CMAKE_MESSAGE_INDENT "  ")
if(Doxygen_FOUND)
    # set input and output files
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/doxygen)
    set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    configure_file(coverage.dox.in ${CMAKE_BINARY_DIR}/coverage/coverage.dox @ONLY)

    file(GLOB_RECURSE PUBLIC_HEADERS "${CMAKE_SOURCE_DIR}/include" PATTERN *.h*)
    file(GLOB_RECURSE PRIVATE_HEADERS "${CMAKE_SOURCE_DIR}/lib" PATTERN *.h*)


    # Command for running examples that have generated images for the documentation
    add_custom_command(OUTPUT ${DOXYGEN_OUTPUT_DIR}/periodogram_example_file
                       COMMAND ${CMAKE_BINARY_DIR}/bin/examples/example-periodogram
                       DEPENDS example-periodogram
                       COMMENT "Running periodogram examples in order to generate documentation images"
                       VERBATIM)

    set(DOC_EXAMPLES_FILES ${DOXYGEN_OUTPUT_DIR}/periodogram_example_file)

    # Command for generating the documentation
    add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                       DEPENDS ${PUBLIC_HEADERS} ${PRIVATE_HEADER} ${DOC_EXAMPLES_FILES}
                       COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
                       MAIN_DEPENDENCY ${DOXYFILE_OUT} ${DOXYFILE_IN}
                       COMMENT "Generating documentation with Doxygen"
                       VERBATIM)

    # note the option ALL which allows to build the docs together with the application
    add_custom_target(doc ALL DEPENDS ${DOXYGEN_INDEX_FILE} ${DOC_EXAMPLES_FILES})

    if(Shinx_FOUND)
        set(SPHINX_SOURCE ${CMAKE_CURRENT_SOURCE_DIR})
        set(SPHINX_BUILD ${CMAKE_CURRENT_BINARY_DIR}/sphinx)
        set(SPHINX_INDEX_FILE ${SPHINX_BUILD}/index.html)

        add_custom_command(OUTPUT ${SPHINX_INDEX_FILE}
                           COMMAND ${SPHINX_EXECUTABLE} -b html -Dbreathe_projects.CppTemplate=${DOXYGEN_OUTPUT_DIR}/xml ${SPHINX_SOURCE} ${SPHINX_BUILD}
                           WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                           DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/index.rst ${DOXYGEN_INDEX_FILE}
                           MAIN_DEPENDENCY ${SPHINX_SOURCE}/conf.py
                           COMMENT "Generating documentation with sphinx"
                           )

        add_custom_target(sphinx ALL DEPENDS ${SPHINX_INDEX_FILE})
    endif()

else()
    message(FATAL "To build the documentation we need doxygen")
endif(Doxygen_FOUND)
list(POP_BACK CMAKE_MESSAGE_INDENT)
