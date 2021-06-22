### GENERATED FILE - DO NOT OVERWRITE ###

cmake_minimum_required(VERSION 3.10)
set(CMAKE_VERBOSE_MAKEFILE FALSE)

# SET VARIABLES
set(N_WS_PATH /cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan)
set(JAVA_HOME /cea/temp/b4/lemairen/NabLab/graalvm-ce-java11-21.0.0)
set(BATHYLIBCPPJNI_PATH ${N_WS_PATH}/swan/src-gen-interpreter/bathylibcppjni)

# PROJECT
project(SwanProject CXX)

# CHECK CXX VERSION: must be done after the project() (CMAKE_CXX_COMPILER_ID not defined before)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.1.0")
		message(FATAL_ERROR "GCC minimum required version is 9.1.0. Please upgrade.")
	endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0.0")
		message(FATAL_ERROR "Clang minimum required version is 9.0.0. Please upgrade.")
	endif()
endif()

# SUB_DIRECTORIES
if(NOT TARGET bathylibcppjni)
	add_subdirectory(${BATHYLIBCPPJNI_PATH} ${CMAKE_BINARY_DIR}/bathylibcppjni)
endif()

# OPTIONAL USER OPTIONS IN Project.cmake
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Project.cmake)
	include(${CMAKE_CURRENT_SOURCE_DIR}/Project.cmake)
endif()
