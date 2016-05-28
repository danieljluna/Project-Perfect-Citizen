cmake_minimum_required (VERSION 3.5.2)
project (ProjectPerfectCitizen)

#-CMake-Config-Vars----------------------------------------------------

# Version Number
set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)
set(Tutorial_VERSION_PATCH 0)

#-Create-Config-File---------------------------------------------------

configure_file(
   "${PROJECT_SOURCE_DIR}/PPC_cmake.h.in"
   "${PROJECT_BINARY_DIR}/PPC_cmake.h"
)

# Add the binary tree to the search path for include files so that
#  we will find PPC_cmake.h
include_directories ("${PROJECT_BINARY_DIR}")

#

if (

add_executable(ProjectPerfectCitizen WIN32)