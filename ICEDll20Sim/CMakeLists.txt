cmake_minimum_required(VERSION 3.1)
set(DLLNAME "ICEDll20Sim")

#DO NOT CHANGE BELOW!
project(${DLLNAME})

 if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( BinFolder "win64" )
  else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
    set( BinFolder "win32" )
  endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )


# Setting output directory for compiler
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "../bin/${BinFolder}" )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "../bin/${BinFolder}" )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "../bin/${BinFolder}" )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Defining include directories and source directories
include_directories(Include/)

file(GLOB SOURCES "src/*.cpp")

#Generating dll and SupportFilesGenerator
add_library(${DLLNAME} SHARED ${SOURCES})
