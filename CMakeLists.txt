# --------------------------------------------
# Project Properties
# --------------------------------------------

cmake_minimum_required(VERSION 3.21)
project(ESMTOOLKIT VERSION 1.0.0 LANGUAGES C CXX)

# --------------------------------------------
# Includes
# --------------------------------------------

include(cmake/utils.cmake)
include(GNUInstallDirs)
include(FetchContent)

# --------------------------------------------
# Project Options
# --------------------------------------------

option(ESMTOOLKIT_INSTALL_TARGETS "Install the project targets" ${PROJECT_IS_TOP_LEVEL})
option(ESMTOOLKIT_BUILD_TEST "Build the project tests" ${PROJECT_IS_TOP_LEVEL})
set_if_undefined(ESMTOOLKIT_INSTALL_CMAKEDIR "${CMAKE_INSTALL_LIBDIR}/cmake/esm" CACHE STRING "Where to install library files")
set_if_undefined(ESMTOOLKIT_DEBUG_POSTFIX "d" CACHE STRING "Debug artifacts postfix")
if (DEFINED ESMTOOLKIT_DEBUG_POSTFIX AND NOT DEFINED CMAKE_DEBUG_POSTFIX)
    set(CMAKE_DEBUG_POSTFIX ${ESMTOOLKIT_DEBUG_POSTFIX})
endif ()


# --------------------------------------------
# Global Properties
# --------------------------------------------

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# --------------------------------------------
# Subprojects
# --------------------------------------------

add_subdirectory(source)
