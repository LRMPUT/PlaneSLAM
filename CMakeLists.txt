cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# Debug
# Release
set(CMAKE_BUILD_TYPE "Release")

project(PlaneSLAM)

SET(CMAKE_CXX_FLAGS "-std=c++11 -g")

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

#g2o library
find_package(G2O REQUIRED)
include_directories(${G2O_INCLUDE_DIR})
link_directories(${G2O_LIBRARY_DIRS})

#Eigen
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/3rdParty/Eigen)
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
add_definitions(-Wno-deprecated -DEIGEN_DONT_VECTORIZE -DEIGEN_DISABLE_UNALIGNED_ARRAY_ASSERT)

include_directories(include)
include_directories(${PROJECT_SOURCE_DIR})

set(PlaneSLAM_SOURCES
	)

add_executable(PlaneSLAM
	${PlaneSLAM_SOURCES}
	src/main.cpp)

target_link_libraries(PlaneSLAM
	${G2O_TYPES_SLAM3D})


