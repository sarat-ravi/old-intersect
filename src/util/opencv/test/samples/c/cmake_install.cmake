# Install script for directory: /home/saratt/Documents/openML/src/util/opencv/samples/c

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

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv/samples/c" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/polar_transforms.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/motempl.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/morphology.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/contours.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/pyramid_segmentation.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/delaunay.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/convert_cascade.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/fback_c.c"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/adaptiveskindetector.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/tree_engine.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/find_obj_calonder.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/one_way_sample.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/bgfg_codebook.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/blobtrack_sample.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/mushroom.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/facedetect.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/find_obj.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/find_obj_ferns.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/latentsvmdetect.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/mser_sample.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/lena.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/one_way_train_0000.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/baboon200_rotated.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/airplane.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/baboon.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/baboon200.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/one_way_train_0001.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/cat.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/fruits.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/stuff.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/box_in_scene.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/puzzle.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/box.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/JCB.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/agaricus-lepiota.data"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/waveform.data"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/build_all.sh"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/cvsample.dsp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/c/facedetect.cmd"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

