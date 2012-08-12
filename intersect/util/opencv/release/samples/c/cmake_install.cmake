# Install script for directory: /Users/saratt/Documents/openML/src/util/opencv/samples/c

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv/samples/c" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/contours.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/convert_cascade.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/delaunay.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/fback_c.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/morphology.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/motempl.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/polar_transforms.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/pyramid_segmentation.c"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/adaptiveskindetector.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/bgfg_codebook.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/blobtrack_sample.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/facedetect.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/find_obj.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/find_obj_calonder.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/find_obj_ferns.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/latentsvmdetect.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/mser_sample.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/mushroom.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/one_way_sample.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/tree_engine.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/airplane.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/baboon.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/baboon200.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/baboon200_rotated.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/cat.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/fruits.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/lena.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/one_way_train_0000.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/one_way_train_0001.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/stuff.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/box.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/box_in_scene.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/JCB.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/puzzle.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/agaricus-lepiota.data"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/waveform.data"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/build_all.sh"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/cvsample.dsp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/c/facedetect.cmd"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

