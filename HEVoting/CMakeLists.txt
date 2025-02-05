cmake_minimum_required(VERSION 3.5)
project(HEVoting CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_PREFIX_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
  ${CMAKE_PREFIX_PATH})

add_executable(${PROJECT_NAME} main.cc)


# ##############################################################################
add_subdirectory(drogon) 
target_link_libraries(${PROJECT_NAME} PRIVATE drogon)

add_subdirectory(seal) 
target_link_libraries(${PROJECT_NAME} PRIVATE seal)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
#find_package(SEAL 4.1.1 REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE SEAL::seal)
find_package(Boost 1.69.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)

find_package(libsodium CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE libsodium::libsodium)

########################################################################

if (CMAKE_C_COMPILER_ID STREQUAL "GNU"
    OR CMAKE_C_COMPILER_ID STREQUAL "Clang")
    set(_GCC_COMPATIBLE 1)
endif()

# static library option
if (NOT DEFINED sodium_USE_STATIC_LIBS)
    option(sodium_USE_STATIC_LIBS "enable to statically link against sodium" OFF)
endif()
if(NOT (sodium_USE_STATIC_LIBS EQUAL sodium_USE_STATIC_LIBS_LAST))
    unset(sodium_LIBRARY CACHE)
    unset(sodium_LIBRARY_DEBUG CACHE)
    unset(sodium_LIBRARY_RELEASE CACHE)
    unset(sodium_DLL_DEBUG CACHE)
    unset(sodium_DLL_RELEASE CACHE)
    set(sodium_USE_STATIC_LIBS_LAST ${sodium_USE_STATIC_LIBS} CACHE INTERNAL "internal change tracking variable")
endif()

# ##############################################################################

#  "${CMAKE_CURRENT_SOURCE_DIR}/CMake"
#  ${CMAKE_MODULE_PATH})
  
#find_package(Sodium REQUIRED)

########################################################################
# UNIX
if (UNIX)
    # import pkg-config

    find_package(PkgConfig QUIET)

    if (PKG_CONFIG_FOUND)
        pkg_check_modules(sodium_PKG QUIET libsodium)
    endif()

    if(sodium_USE_STATIC_LIBS)
        foreach(_libname ${sodium_PKG_STATIC_LIBRARIES})
            if (NOT _libname MATCHES "^lib.*\\.a$") # ignore strings already ending with .a
                list(INSERT sodium_PKG_STATIC_LIBRARIES 0 "lib${_libname}.a")
            endif()
        endforeach()
        list(REMOVE_DUPLICATES sodium_PKG_STATIC_LIBRARIES)

        # if pkgconfig for libsodium doesn't provide
        # static lib info, then override PKG_STATIC here..
        if (NOT sodium_PKG_STATIC_FOUND)
            set(sodium_PKG_STATIC_LIBRARIES libsodium.a)
        endif()

        set(XPREFIX sodium_PKG_STATIC)
    else()
        if (NOT sodium_PKG_FOUND)
            set(sodium_PKG_LIBRARIES sodium)
        endif()

        set(XPREFIX sodium_PKG)
    endif()

    find_path(sodium_INCLUDE_DIR sodium.h
        HINTS ${${XPREFIX}_INCLUDE_DIRS}
    )
    find_library(sodium_LIBRARY_DEBUG NAMES ${${XPREFIX}_LIBRARIES}
        HINTS ${${XPREFIX}_LIBRARY_DIRS}
    )
    find_library(sodium_LIBRARY_RELEASE NAMES ${${XPREFIX}_LIBRARIES}
        HINTS ${${XPREFIX}_LIBRARY_DIRS}
    )


########################################################################
# unsupported
else()
    message(FATAL_ERROR "this platform is not supported by FindSodium.cmake")
endif()


########################################################################
# common stuff

# extract sodium version
if (sodium_INCLUDE_DIR)
    set(_VERSION_HEADER "${_INCLUDE_DIR}/sodium/version.h")
    if (EXISTS _VERSION_HEADER)
        file(READ "${_VERSION_HEADER}" _VERSION_HEADER_CONTENT)
        string(REGEX REPLACE ".*#[ \t]*define[ \t]*SODIUM_VERSION_STRING[ \t]*\"([^\n]*)\".*" "\\1"
            sodium_VERSION "${_VERSION_HEADER_CONTENT}")
        set(sodium_VERSION "${sodium_VERSION}" PARENT_SCOPE)
    endif()
endif()

# communicate results
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    Sodium # The name must be either uppercase or match the filename case.
    REQUIRED_VARS
        sodium_LIBRARY_RELEASE
        sodium_LIBRARY_DEBUG
        sodium_INCLUDE_DIR
    VERSION_VAR
        sodium_VERSION
)

if(Sodium_FOUND)
    set(sodium_LIBRARIES
        optimized ${sodium_LIBRARY_RELEASE} debug ${sodium_LIBRARY_DEBUG})
endif()

# mark file paths as advanced
mark_as_advanced(sodium_INCLUDE_DIR)
mark_as_advanced(sodium_LIBRARY_DEBUG)
mark_as_advanced(sodium_LIBRARY_RELEASE)
if (WIN32)
    mark_as_advanced(sodium_DLL_DEBUG)
    mark_as_advanced(sodium_DLL_RELEASE)
endif()

# create imported target
if(sodium_USE_STATIC_LIBS)
    set(_LIB_TYPE STATIC)
else()
    set(_LIB_TYPE SHARED)
endif()

if(NOT TARGET sodium)
    add_library(sodium ${_LIB_TYPE} IMPORTED)
endif()

set_target_properties(sodium PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "${sodium_INCLUDE_DIR}"
    IMPORTED_LINK_INTERFACE_LANGUAGES "C"
)

if (sodium_USE_STATIC_LIBS)
    set_target_properties(sodium PROPERTIES
        INTERFACE_COMPILE_DEFINITIONS "SODIUM_STATIC"
        IMPORTED_LOCATION "${sodium_LIBRARY_RELEASE}"
        IMPORTED_LOCATION_DEBUG "${sodium_LIBRARY_DEBUG}"
    )
else()
    if (UNIX)
        set_target_properties(sodium PROPERTIES
            IMPORTED_LOCATION "${sodium_LIBRARY_RELEASE}"
            IMPORTED_LOCATION_DEBUG "${sodium_LIBRARY_DEBUG}"
        )
    elseif (WIN32)
        set_target_properties(sodium PROPERTIES
            IMPORTED_IMPLIB "${sodium_LIBRARY_RELEASE}"
            IMPORTED_IMPLIB_DEBUG "${sodium_LIBRARY_DEBUG}"
        )
        if (NOT (sodium_DLL_DEBUG MATCHES ".*-NOTFOUND"))
            set_target_properties(sodium PROPERTIES
                IMPORTED_LOCATION_DEBUG "${sodium_DLL_DEBUG}"
            )
        endif()
        if (NOT (sodium_DLL_RELEASE MATCHES ".*-NOTFOUND"))
            set_target_properties(sodium PROPERTIES
                IMPORTED_LOCATION_RELWITHDEBINFO "${sodium_DLL_RELEASE}"
                IMPORTED_LOCATION_MINSIZEREL "${sodium_DLL_RELEASE}"
                IMPORTED_LOCATION_RELEASE "${sodium_DLL_RELEASE}"
            )
        endif()
    endif()
endif()



if (CMAKE_CXX_STANDARD LESS 17)
    # With C++14, use boost to support any, string_view and filesystem
    message(STATUS "use c++14")
    find_package(Boost 1.69.0 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)
elseif (CMAKE_CXX_STANDARD LESS 20)
    message(STATUS "use c++17")
else ()
    message(STATUS "use c++20")
endif ()

aux_source_directory(controllers CTL_SRC)
aux_source_directory(filters FILTER_SRC)
aux_source_directory(plugins PLUGIN_SRC)
aux_source_directory(models MODEL_SRC)

drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})
# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)
# use the following line to create views with namespace CHANGE_ME prefixed
# and path namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE CHANGE_ME)

target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models)
target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC} "util/Trie.h"  )
# ##############################################################################
# uncomment the following line for dynamically loading views 
# set_property(TARGET ${PROJECT_NAME} PROPERTY ENABLE_EXPORTS ON)

# ##############################################################################

#add_subdirectory(test)
