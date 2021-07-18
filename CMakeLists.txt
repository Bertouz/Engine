cmake_minimum_required(VERSION 3.14)

project(MyCppProject
    VERSION 0.0.1
    LANGUAGES CXX
    )

## When we do conan install we download and/or build the dependencies
## Then a conanbuildinfo.cmake file is generated with the variables defining the targets
## to those dependencies

#############################
### Project Options
#############################
include(CMakeDependentOption)

option(BUILD_DOC "Build documentation" OFF) 
option(BUILD_TESTS "Build unit testing" OFF)
option(USE_CONAN "Define if we want to use conan for handling dependencies if its available" OFF)
option(ENABLE_CODE_COVERAGE "Add gcov/lcov analysis to process" OFF)
option(ENABLE_CLANG_TIDY "Add clang-tidy analysis to source code" OFF)
option(ENABLE_CLANG_FORMAT "Add clang-format to build process" OFF)
option(ENABLE_MICRO_BENCHMARKS "Build project microbenchmarks" OFF)
cmake_dependent_option(ENABLE_MEMCHECK "Add memory check to unit test" ON BUILD_TESTS OFF)


####################################
### Include cmake scripts and config
####################################
if(EXISTS ${CMAKE_BINARY_DIR}/conaninfo.txt)
	set(USE_CONAN ON)
endif()

if(USE_CONAN)
	message(STATUS "Using conan generated FindXXX.cmake files")
	list(PREPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
endif()

if(CONAN_CXX_COMPILER)
	set(CMAKE_CXX_STANDARD ${CONAN_CMAKE_CXX_COMPILER})
endif()

if(CONAN_CMAKE_CXX_STANDARD)
	set(CMAKE_CXX_STANDARD ${CONAN_CMAKE_CXX_STANDARD})
else()
	set(CMAKE_CXX_STANDARD 14)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(FindPackageHandleStandardArgs)

if(ENABLE_CLANG_TIDY)
    message(STATUS "Enabling code static analysis with clang-tidy")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    include(UseClangTidy)
    list(POP_BACK CMAKE_MESSAGE_INDENT)
endif(ENABLE_CLANG_TIDY)

if(ENABLE_CLANG_FORMAT)
    message(STATUS "Enabling code formatting with clang-format")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    include(UseClangFormat)
    list(POP_BACK CMAKE_MESSAGE_INDENT)
endif(ENABLE_CLANG_FORMAT)

if(ENABLE_CODE_COVERAGE)
    message(STATUS "Enabling code coverage with gcov")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
    include(UseCodeCoverage)
    append_coverage_compiler_flags()
    setup_target_for_coverage_gcovr_html(
        NAME coverage
        EXECUTABLE ctest
        DEPENCIES testu
        EXCLUDE tests
        )
    list(POP_BACK CMAKE_MESSAGE_INDENT )
endif(ENABLE_CODE_COVERAGE)

if(ENABLE_MICRO_BENCHMARKS)
    message(STATUS "Enabling project microbenchmarks")
    list(APPEND CMAKE_MESSAGE_INDENT "  ")
	find_package(benchmark REQUIRED)
    list(POP_BACK CMAKE_MESSAGE_INDENT )
endif(ENABLE_MICRO_BENCHMARKS)

if (CMAKE_BINARY_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()



#############################
### Dependencies
#############################
# I prefer to look for all the dependecies at the start
# to avoid a user to look for different find_package in dedicated subdirectory
# Also if possible I add the possibility to use external dependencies in submodules to simplify a first use

if(BUILD_DOC)
	find_package(Doxygen REQUIRED)
	#find_package(Sphinx REQUIRED)
	find_program(SPHINX_EXECUTABLE NAMES sphinx-build DOC "Path to sphinx-build executable")
	find_package_handle_standard_args(Sphinx "Failed to find sphinx-build executable" SPHINX_EXECUTABLE)
endif(BUILD_DOC)

if(BUILD_TESTS)
    if(NOT Catch2_FOUND)
	find_package(Catch2 3 REQUIRED)
    endif()

    if(ENABLE_MEMCHECK)
        message(STATUS "Looking for valgrind")
        list(APPEND CMAKE_MESSAGE_INDENT "  ")
        find_program(MEMORYCHECK_COMMAND valgrind)
    	set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")
    	set(MEMORYCHECK_SUPPRESSIONS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/valgrind_suppress.txt")
    	message(STATUS "MEMORYCHECK_COMMAND           = ${MEMORYCHECK_COMMAND}")
    	message(STATUS "MEMORYCHECK_COMMAND_OPTIONS   = ${MEMORYCHECK_COMMAND_OPTIONS}")
    	message(STATUS "MEMORYCHECK_SUPPRESSIONS_FILE = ${MEMORYCHECK_SUPPRESSIONS_FILE}")
        list(POP_BACK CMAKE_MESSAGE_INDENT)
    endif(ENABLE_MEMCHECK)

endif(BUILD_TESTS)

#############################
### Project
#############################

if(BUILD_TESTS)
    include(CTest)
endif(BUILD_TESTS)

add_subdirectory(project)



#############################
### Documentation
#############################
if(BUILD_DOC)
   add_subdirectory(doc)
endif(BUILD_DOC)


#############################
### Installation
#############################

# Install documentation
if(BUILD_DOC)
    install( DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/doc/doxygen" DESTINATION "${CMAKE_INSTALL_DOCDIR}" )
endif(BUILD_DOC)

# Configuration
set(config_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")
set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Write the version config file
write_basic_package_version_file( "${version_config}" COMPATIBILITY SameMajorVersion )

# Write package config file
configure_package_config_file(
    "cmake/MyCppProjectConfig.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Install targets
install(
    TARGETS app1 lib1 lib2 #plus others if there is
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}/"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}/"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
)

#Install version config file
install( FILES "${project_config}" "${version_config}" DESTINATION "${config_install_dir}" )

#Install config file for exported targets
install( EXPORT "${TARGETS_EXPORT_NAME}" NAMESPACE "${namespace}" DESTINATION "${config_install_dir}" )

