# PPC CMAKE ROOT

cmake_minimum_required (VERSION 3.5.2)
project (ProjectPerfectCitizen)

#-CMake-Config-Vars----------------------------------------------------

# Version Number
set(Tutorial_VERSION_MAJOR 1)
set(Tutorial_VERSION_MINOR 0)
set(Tutorial_VERSION_PATCH 0)

#-Make-Sub-Directories-------------------------------------------------

# Compile Game
add_subdirectory(Game)
add_subdirectory(Engine)
add_subdirectory(Library)

#-Create-Exe-----------------------------------------------------------

add_executable(ProjectPerfectCitizen main.cpp)