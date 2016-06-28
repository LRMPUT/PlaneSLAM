# Install script for directory: /home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg2o_parser.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/lib/libg2o_parser.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/slam_parser/parser/FlexLexer.h;/usr/local/include/slam_parser/parser/bison_parser.h;/usr/local/include/slam_parser/parser/scanner.h;/usr/local/include/slam_parser/parser/slam_context.h;/usr/local/include/slam_parser/parser/commands.h;/usr/local/include/slam_parser/parser/driver.h;/usr/local/include/slam_parser/parser/stack.hh;/usr/local/include/slam_parser/parser/location.hh;/usr/local/include/slam_parser/parser/position.hh")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/slam_parser/parser" TYPE FILE FILES
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/FlexLexer.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/bison_parser.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/scanner.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/slam_context.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/commands.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/driver.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/stack.hh"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/location.hh"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples/interactive_slam/slam_parser/parser/position.hh"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

