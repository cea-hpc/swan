# Install script for directory: /cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib" TYPE SHARED_LIBRARY FILES "/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/swan/build/bathylibcppjni/libbathylibcppjni.so")
  if(EXISTS "$ENV{DESTDIR}/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/libbathylibcppjni.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib/bathylibcppjni.jar")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/bathylibcppjni/lib" TYPE FILE FILES "/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/swan/build/bathylibcppjni/bathylibcppjni.jar")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/swan/build/nablalib/cmake_install.cmake")
  include("/cea/dsku/u-pong/temp1/b4/lemairen/Workspace/swan/swan/src-gen-interpreter/swan/build/bathylibcpp/cmake_install.cmake")

endif()

