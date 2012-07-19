# Install script for directory: /home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/eigen3/Eigen/CholmodSupport;/usr/local/include/eigen3/Eigen/Jacobi;/usr/local/include/eigen3/Eigen/StdDeque;/usr/local/include/eigen3/Eigen/Dense;/usr/local/include/eigen3/Eigen/LU;/usr/local/include/eigen3/Eigen/StdVector;/usr/local/include/eigen3/Eigen/SparseCholesky;/usr/local/include/eigen3/Eigen/Sparse;/usr/local/include/eigen3/Eigen/Householder;/usr/local/include/eigen3/Eigen/UmfPackSupport;/usr/local/include/eigen3/Eigen/Eigenvalues;/usr/local/include/eigen3/Eigen/SuperLUSupport;/usr/local/include/eigen3/Eigen/Core;/usr/local/include/eigen3/Eigen/OrderingMethods;/usr/local/include/eigen3/Eigen/PaStiXSupport;/usr/local/include/eigen3/Eigen/Cholesky;/usr/local/include/eigen3/Eigen/QR;/usr/local/include/eigen3/Eigen/PardisoSupport;/usr/local/include/eigen3/Eigen/StdList;/usr/local/include/eigen3/Eigen/Array;/usr/local/include/eigen3/Eigen/SparseCore;/usr/local/include/eigen3/Eigen/SVD;/usr/local/include/eigen3/Eigen/LeastSquares;/usr/local/include/eigen3/Eigen/Geometry;/usr/local/include/eigen3/Eigen/QtAlignedMalloc;/usr/local/include/eigen3/Eigen/IterativeLinearSolvers;/usr/local/include/eigen3/Eigen/Eigen;/usr/local/include/eigen3/Eigen/Eigen2Support")
FILE(INSTALL DESTINATION "/usr/local/include/eigen3/Eigen" TYPE FILE FILES
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/CholmodSupport"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Jacobi"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/StdDeque"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Dense"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/LU"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/StdVector"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/SparseCholesky"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Sparse"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Householder"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/UmfPackSupport"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Eigenvalues"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/SuperLUSupport"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Core"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/OrderingMethods"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/PaStiXSupport"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Cholesky"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/QR"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/PardisoSupport"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/StdList"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Array"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/SparseCore"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/SVD"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/LeastSquares"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Geometry"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/QtAlignedMalloc"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/IterativeLinearSolvers"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Eigen"
    "/home/saratt/Documents/openML/src/util/eigenCppLibrary/Eigen/Eigen2Support"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Devel")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/saratt/Documents/openML/src/util/eigenCppLibrary/eigenRelease/Eigen/src/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

