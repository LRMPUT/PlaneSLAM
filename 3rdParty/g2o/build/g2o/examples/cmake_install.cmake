# Install script for directory: /home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/examples

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

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/data_fitting/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/sphere/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/target/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/ba/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/ba_anchored_inverse_depth/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/tutorial_slam2d/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/icp/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/calibration_odom_laser/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/simple_optimize/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/plane_slam/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/sba/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/bal/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/slam2d/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/data_convert/cmake_install.cmake")
  INCLUDE("/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/build/g2o/examples/interactive_slam/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

