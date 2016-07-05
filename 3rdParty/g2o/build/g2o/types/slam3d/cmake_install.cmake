# Install script for directory: /home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d

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
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
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
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_types_slam3d_d.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_types_slam3d_d.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_types_slam3d_d.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg2o_types_slam3d_d.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/lib/libg2o_types_slam3d_d.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_types_slam3d_d.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_types_slam3d_d.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_types_slam3d_d.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libg2o_types_slam3d_d.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g2o/types/slam3d/vertex_se3.h;/usr/local/include/g2o/types/slam3d/isometry3d_mappings.h;/usr/local/include/g2o/types/slam3d/edge_se3_pointxyz.h;/usr/local/include/g2o/types/slam3d/g2o_types_slam3d_api.h;/usr/local/include/g2o/types/slam3d/edge_se3.h;/usr/local/include/g2o/types/slam3d/parameter_stereo_camera.h;/usr/local/include/g2o/types/slam3d/edge_se3_lotsofxyz.h;/usr/local/include/g2o/types/slam3d/isometry3d_gradients.h;/usr/local/include/g2o/types/slam3d/vertex_plane_quat.h;/usr/local/include/g2o/types/slam3d/edge_se3_prior.h;/usr/local/include/g2o/types/slam3d/edge_se3_plane.h;/usr/local/include/g2o/types/slam3d/se3quat.h;/usr/local/include/g2o/types/slam3d/types_slam3d.h;/usr/local/include/g2o/types/slam3d/dquat2mat.h;/usr/local/include/g2o/types/slam3d/vertex_se3_quat.h;/usr/local/include/g2o/types/slam3d/parameter_camera.h;/usr/local/include/g2o/types/slam3d/parameter_se3_offset.h;/usr/local/include/g2o/types/slam3d/edge_se3_pointxyz_depth.h;/usr/local/include/g2o/types/slam3d/vertex_pointxyz.h;/usr/local/include/g2o/types/slam3d/edge_se3_pointxyz_disparity.h;/usr/local/include/g2o/types/slam3d/se3_ops.h;/usr/local/include/g2o/types/slam3d/edge_pointxyz.h;/usr/local/include/g2o/types/slam3d/edge_se3_pointxyz_reprojectionError.h;/usr/local/include/g2o/types/slam3d/edge_se3_offset.h;/usr/local/include/g2o/types/slam3d/se3_ops.hpp")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/g2o/types/slam3d" TYPE FILE FILES
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/vertex_se3.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/isometry3d_mappings.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_pointxyz.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/g2o_types_slam3d_api.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/parameter_stereo_camera.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_lotsofxyz.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/isometry3d_gradients.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/vertex_plane_quat.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_prior.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_plane.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/se3quat.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/types_slam3d.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/dquat2mat.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/vertex_se3_quat.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/parameter_camera.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/parameter_se3_offset.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_pointxyz_depth.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/vertex_pointxyz.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_pointxyz_disparity.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/se3_ops.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_pointxyz.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_pointxyz_reprojectionError.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/edge_se3_offset.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/types/slam3d/se3_ops.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

