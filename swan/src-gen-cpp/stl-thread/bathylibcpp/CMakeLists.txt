### DO NOT EDIT THIS FILE - it is machine generated ###

# This file is in a cmake sub_directory and is called by a root CMakeLists.txt 

# CHECK VARIABLES
if (NOT DEFINED N_WS_PATH)
	message(FATAL_ERROR "N_WS_PATH variable must be set")
endif()

# SUB_DIRECTORIES
if(NOT TARGET nablalib)
	add_subdirectory(${N_WS_PATH}/.nablab/nablalib ${CMAKE_BINARY_DIR}/nablalib)
endif()

# LIBRARY bathylibcpp
add_library(bathylibcpp BathyLib.cc)
set_property(TARGET bathylibcpp PROPERTY POSITION_INDEPENDENT_CODE ON)
target_compile_options(bathylibcpp PUBLIC -g -Wall -O3 --std=c++17 -mtune=native)
target_include_directories(bathylibcpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bathylibcpp PUBLIC nablalib pthread)

# OPTIONAL USER OPTIONS IN Project.cmake
if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Project.cmake)
	include(${CMAKE_CURRENT_SOURCE_DIR}/Project.cmake)
endif()
