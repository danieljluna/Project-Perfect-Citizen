# PPC CMAKE ROOT

cmake_minimum_required (VERSION 3.5.2)
project (ProjectPerfectCitizen)

#-CMake-Config-Vars----------------------------------------------------

# Version Number
set(PPC_VERSION_MAJOR 1)
set(PPC_VERSION_MINOR 0)
set(PPC_VERSION_PATCH 0)

if (WIN32)
   add_definitions(-DWINDOWS_MARKER)
endif ()

#-Make-Sub-Directories-------------------------------------------------

file(GLOB_RECURSE PPC_SOURCES "./*.cpp")
file(GLOB_RECURSE PPC_HEADERS_H "./*.h")
file(GLOB_RECURSE PPC_HEADERS_HPP "./*.hpp")

set(PPC_HEADERS ${PPC_HEADERS_H} ${PPC_HEADERS_HPP})

set (PPC_INCLUDE_DIRS "")
foreach (_headerFile ${PPC_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND PPC_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES PPC_INCLUDE_DIRS)

include_directories(${PPC_INCLUDE_DIRS})

#-Create-Exe-----------------------------------------------------------

set(EXECUTABLE_NAME "ProjectPerfectCitizen")
add_executable(${EXECUTABLE_NAME} main.cpp ${PPC_SOURCES} ${PPC_HEADERS})


set(CMAKE_MODULE_PATH ${SFML_DIR})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics audio)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

#Include Resources folder
include_directories("../Resources")


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION .)

install(PROGRAMS 
   ${CMAKE_CURRENT_SOURCE_DIR}/../Redist/vc_redist.x86.exe
   DESTINATION tmp)
          
list(APPEND CPACK_NSIS_EXTRA_INSTALL_COMMANDS " 
   ExecWait '$INSTDIR\\\\tmp\\\\vc_redist.x86.exe'
   ")

#CPack packaging
include(InstallRequiredSystemLibraries)
if (WIN32)
   set(CPACK_GENERATOR NISIS)
   set(CPACK_NSIS_MODIFY_PATH ON)
else ()
   
endif()
set(CPACK_PACKAGE_NAME "Project Perfect Citizen")
set(CPACK_PACKAGE_VENDOR "Bad Cop Studios")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Placeholder Summary")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Project-Perfect-Citizen-${PPC_VERSION_MAJOR}.${PPC_VERSION_MINOR}.${PPC_VERSION_PATCH}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PPC_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PPC_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PPC_VERSION_PATCH}")
include(CPACK)