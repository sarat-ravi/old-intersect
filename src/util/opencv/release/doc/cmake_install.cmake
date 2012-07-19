# Install script for directory: /Users/saratt/Documents/openML/src/util/opencv/doc

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
    SET(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OpenCV/doc" TYPE FILE FILES
    "/Users/saratt/Documents/openML/src/util/opencv/doc/haartraining.htm"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/check_docs_whitelist.txt"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/CMakeLists.txt"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/license.txt"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/packaging.txt"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/acircles_pattern.png"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv-logo-white.png"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv-logo.png"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv-logo2.png"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/pattern.png"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv2refman.pdf"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv_cheatsheet.pdf"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv_tutorials.pdf"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/opencv_user.pdf"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/OpenCV/doc/vidsurv" TYPE FILE FILES
    "/Users/saratt/Documents/openML/src/util/opencv/doc/vidsurv/Blob_Tracking_Modules.doc"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/vidsurv/Blob_Tracking_Tests.doc"
    "/Users/saratt/Documents/openML/src/util/opencv/doc/vidsurv/TestSeq.doc"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "main")

