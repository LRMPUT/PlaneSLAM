# Install script for directory: /home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core

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
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_core_d.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_core_d.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_core_d.so"
         RPATH "")
  ENDIF()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg2o_core_d.so")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/lib/libg2o_core_d.so")
  IF(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_core_d.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_core_d.so")
    FILE(RPATH_REMOVE
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_core_d.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libg2o_core_d.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g2o/core/base_multi_edge.h;/usr/local/include/g2o/core/matrix_operations.h;/usr/local/include/g2o/core/parameter.h;/usr/local/include/g2o/core/optimizable_graph.h;/usr/local/include/g2o/core/creators.h;/usr/local/include/g2o/core/hyper_graph_action.h;/usr/local/include/g2o/core/robust_kernel_factory.h;/usr/local/include/g2o/core/batch_stats.h;/usr/local/include/g2o/core/marginal_covariance_cholesky.h;/usr/local/include/g2o/core/base_vertex.h;/usr/local/include/g2o/core/eigen_types.h;/usr/local/include/g2o/core/hyper_graph.h;/usr/local/include/g2o/core/sparse_optimizer.h;/usr/local/include/g2o/core/cache.h;/usr/local/include/g2o/core/linear_solver.h;/usr/local/include/g2o/core/sparse_block_matrix.h;/usr/local/include/g2o/core/matrix_structure.h;/usr/local/include/g2o/core/base_unary_edge.h;/usr/local/include/g2o/core/base_edge.h;/usr/local/include/g2o/core/base_binary_edge.h;/usr/local/include/g2o/core/optimization_algorithm.h;/usr/local/include/g2o/core/optimization_algorithm_dogleg.h;/usr/local/include/g2o/core/hyper_dijkstra.h;/usr/local/include/g2o/core/g2o_core_api.h;/usr/local/include/g2o/core/optimization_algorithm_levenberg.h;/usr/local/include/g2o/core/optimization_algorithm_factory.h;/usr/local/include/g2o/core/solver.h;/usr/local/include/g2o/core/block_solver.h;/usr/local/include/g2o/core/openmp_mutex.h;/usr/local/include/g2o/core/optimization_algorithm_property.h;/usr/local/include/g2o/core/sparse_optimizer_terminate_action.h;/usr/local/include/g2o/core/optimization_algorithm_gauss_newton.h;/usr/local/include/g2o/core/robust_kernel.h;/usr/local/include/g2o/core/parameter_container.h;/usr/local/include/g2o/core/factory.h;/usr/local/include/g2o/core/sparse_block_matrix_ccs.h;/usr/local/include/g2o/core/sparse_block_matrix_diagonal.h;/usr/local/include/g2o/core/robust_kernel_impl.h;/usr/local/include/g2o/core/estimate_propagator.h;/usr/local/include/g2o/core/optimization_algorithm_with_hessian.h;/usr/local/include/g2o/core/jacobian_workspace.h;/usr/local/include/g2o/core/base_unary_edge.hpp;/usr/local/include/g2o/core/base_binary_edge.hpp;/usr/local/include/g2o/core/block_solver.hpp;/usr/local/include/g2o/core/sparse_block_matrix.hpp;/usr/local/include/g2o/core/base_multi_edge.hpp;/usr/local/include/g2o/core/base_vertex.hpp")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/g2o/core" TYPE FILE FILES
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_multi_edge.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/matrix_operations.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/parameter.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimizable_graph.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/creators.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/hyper_graph_action.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/robust_kernel_factory.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/batch_stats.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/marginal_covariance_cholesky.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_vertex.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/eigen_types.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/hyper_graph.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/sparse_optimizer.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/cache.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/linear_solver.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/sparse_block_matrix.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/matrix_structure.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_unary_edge.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_edge.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_binary_edge.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimization_algorithm.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimization_algorithm_dogleg.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/hyper_dijkstra.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/g2o_core_api.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimization_algorithm_levenberg.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimization_algorithm_factory.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/solver.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/block_solver.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/openmp_mutex.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimization_algorithm_property.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/sparse_optimizer_terminate_action.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimization_algorithm_gauss_newton.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/robust_kernel.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/parameter_container.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/factory.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/sparse_block_matrix_ccs.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/sparse_block_matrix_diagonal.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/robust_kernel_impl.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/estimate_propagator.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/optimization_algorithm_with_hessian.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/jacobian_workspace.h"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_unary_edge.hpp"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_binary_edge.hpp"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/block_solver.hpp"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/sparse_block_matrix.hpp"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_multi_edge.hpp"
    "/home/jachu/workspace/PlaneSLAM/3rdParty/g2o/g2o/core/base_vertex.hpp"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

