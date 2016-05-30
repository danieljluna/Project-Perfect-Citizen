# PPC CMAKE ROOT

cmake_minimum_required (VERSION 3.5.2)
project (ProjectPerfectCitizen)

#-CMake-Config-Vars----------------------------------------------------

# Version Number
set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)
set(Tutorial_VERSION_PATCH 0)

#-Make-Sub-Directories-------------------------------------------------

file(GLOB_RECURSE PPC_SOURCES "../*.cpp")
file(GLOB_RECURSE PPC_HEADERS_H "../*.h")
file(GLOB_RECURSE PPC_HEADERS_HPP "../*.hpp")

set(PPC_HEADERS ${PPC_HEADERs_H} ${PPC_HEADERS_HPP})

set (PPC_INCLUDE_DIRS "")
foreach (_headerFile ${PPC_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PPC_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES PPC_INCLUDE_DIRS)

include_directories(${Foo_INCLUDE_DIRS})

#-Create-Exe-----------------------------------------------------------

add_executable(ProjectPerfectCitizen main.cpp ${PPC_SOURCES})