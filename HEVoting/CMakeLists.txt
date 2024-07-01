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

add_executable(${PROJECT_NAME} main.cc)

# ##############################################################################
# If you include the drogon source code locally in your project, use this method
# to add drogon 
# add_subdirectory(drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
#
# and comment out the following lines
find_package(Drogon CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
find_package(SEAL 4.1.1 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SEAL::seal)
find_package(Boost 1.85.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost)

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



# ##############################################################################

if (CMAKE_CXX_STANDARD LESS 17)
    # With C++14, use boost to support any, string_view and filesystem
    message(STATUS "use c++14")
    find_package(Boost 1.61.0 REQUIRED)
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

add_subdirectory(test)