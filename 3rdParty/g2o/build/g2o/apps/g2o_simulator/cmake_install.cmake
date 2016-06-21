# Install script for directory: /home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator

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
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_simulator.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_simulator.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_simulator.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg2o_simulator.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/lib/libg2o_simulator.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_simulator.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_simulator.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_simulator.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libg2o_simulator.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/g2o_simulator2d" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/g2o_simulator2d")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/g2o_simulator2d"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/g2o_simulator2d")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/bin/g2o_simulator2d")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/g2o_simulator2d" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/g2o_simulator2d")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/bin/g2o_simulator2d")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/g2o_simulator2d")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/g2o_simulator3d" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/g2o_simulator3d")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/g2o_simulator3d"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/g2o_simulator3d")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/bin/g2o_simulator3d")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/g2o_simulator3d" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/g2o_simulator3d")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/bin/g2o_simulator3d")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/g2o_simulator3d")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/g2o_anonymize_observations" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/g2o_anonymize_observations")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/bin/g2o_anonymize_observations"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/bin/g2o_anonymize_observations")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/bin" TYPE EXECUTABLE FILES "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/bin/g2o_anonymize_observations")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/bin/g2o_anonymize_observations" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/bin/g2o_anonymize_observations")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/bin/g2o_anonymize_observations")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/bin/g2o_anonymize_observations")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g2o/apps/g2o_simulator/sensor_odometry.h;/usr/local/include/g2o/apps/g2o_simulator/simulator2d_base.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pose2d.h;/usr/local/include/g2o/apps/g2o_simulator/simulator3d.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_odometry3d.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_odometry2d.h;/usr/local/include/g2o/apps/g2o_simulator/simulator3d_base.h;/usr/local/include/g2o/apps/g2o_simulator/pointsensorparameters.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pose3d.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_segment2d_line.h;/usr/local/include/g2o/apps/g2o_simulator/g2o_simulator_api.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_segment2d_pointline.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pointxy_bearing.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_se3_prior.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pointxyz_depth.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pose3d_offset.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pointxyz_disparity.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_line3d.h;/usr/local/include/g2o/apps/g2o_simulator/simutils.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pointxyz.h;/usr/local/include/g2o/apps/g2o_simulator/simulator.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pointxy_offset.h;/usr/local/include/g2o/apps/g2o_simulator/simulator2d.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_pointxy.h;/usr/local/include/g2o/apps/g2o_simulator/sensor_segment2d.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/g2o/apps/g2o_simulator" TYPE FILE FILES
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_odometry.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/simulator2d_base.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pose2d.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/simulator3d.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_odometry3d.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_odometry2d.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/simulator3d_base.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/pointsensorparameters.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pose3d.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_segment2d_line.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/g2o_simulator_api.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_segment2d_pointline.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pointxy_bearing.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_se3_prior.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pointxyz_depth.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pose3d_offset.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pointxyz_disparity.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_line3d.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/simutils.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pointxyz.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/simulator.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pointxy_offset.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/simulator2d.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_pointxy.h"
    "/home/jachu/workspace/PUTSLAM/3rdParty/g2o/g2o/apps/g2o_simulator/sensor_segment2d.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

