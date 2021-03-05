### GENERATED FILE - DO NOT OVERWRITE ###

cmake_minimum_required(VERSION 3.10)

set(LIBCPPNABLA_DIR $ENV{HOME}/workspaces/swan/swan/../LibCppNabla CACHE STRING "")
set(NABLA_CXX_COMPILER /usr/bin/g++)
set(BATHYLIB_DIR $ENV{HOME}/workspaces/swan/swan/../swan/src-gen-cpp/stl-thread/bathylib)

project(SwanProject CXX)

set(CMAKE_CXX_COMPILER ${NABLA_CXX_COMPILER} CACHE STRING "")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "7.4.0")
		message(FATAL_ERROR "GCC minimum required version is 7.4.0. Please upgrade.")
	endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0.0")
		message(FATAL_ERROR "Clang minimum required version is 9.0.0. Please upgrade.")
	endif()
endif()

if(NOT TARGET bathylib)
	add_subdirectory(${BATHYLIB_DIR} ${CMAKE_BINARY_DIR}/BathyLibCpp EXCLUDE_FROM_ALL)
endif()
if(NOT TARGET cppnabla)
	add_subdirectory(${LIBCPPNABLA_DIR} ${CMAKE_BINARY_DIR}/LibCppNabla EXCLUDE_FROM_ALL)
endif()


add_executable(swan Swan.cc)
target_include_directories(swan PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(swan PUBLIC cppnabla cppnablastl pthread bathylib)

if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Project.cmake)
	include(${CMAKE_CURRENT_SOURCE_DIR}/Project.cmake)
endif()
