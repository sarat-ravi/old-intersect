# Install script for directory: /home/saratt/Documents/openML/src/util/opencv/samples/cpp

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv/samples/cpp" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/rgbdodometry.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/retinaDemo.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/contours2.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/stereo_match.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/lkdemo.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/em.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/latentsvm_multidetect.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/stitching_detailed.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/stitching.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/descriptor_extractor_matcher.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/houghlines.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/video_dmtx.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/kmeans.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/inpaint.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/detector_descriptor_matcher_evaluation.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/minarea.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/stereo_calib.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/3calibration.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/cout_mat.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/filestorage.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/facerec_demo.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/image.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/houghcircles.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/starter_imagelist.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/bagofwords_classification.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/kalman.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/point_cloud.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/squares.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/dft.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/demhist.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/fback.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/drawing.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/gencolors.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/calibration_artificial.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/detection_based_tracker_sample.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/OpenEXRimages_HighDynamicRange_Retina_toneMapping.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/distrans.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/openni_capture.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/grabcut.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/peopledetect.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/fitellipse.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/matcher_simple.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/morphology2.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/convexhull.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/meanshift_segmentation.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/video_homography.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/laplace.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/camshiftdemo.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/linemod.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/calibration.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/delaunay2.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/ffilldemo.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/hybridtrackingsample.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/logpolar_bsm.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/build3dmodel.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/watershed.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/connected_components.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/segment_objects.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/videostab.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/bgfg_segm.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/edge.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/letter_recog.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/matching_to_many_images.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/select3dobj.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/points_classifier.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/chamfer.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/phase_corr.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/imagelist_creator.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/brief_match_test.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/opencv_version.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/multicascadeclassifier.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/OpenEXRimages_HighDynamicRange_Retina_toneMapping_video.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/starter_video.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/detector_descriptor_evaluation.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/generic_descriptor_match.cpp"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/lena.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left02.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right02.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left09.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left06.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/board.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right12.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left14.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left01.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left11.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/building.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left08.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/baboon.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left04.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right09.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left03.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left12.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right13.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right07.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left05.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right01.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right11.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/fruits.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right04.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/stuff.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right05.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left13.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right08.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right14.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/left07.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right06.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/right03.jpg"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/logo.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/pic5.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/tsukuba_r.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/pic4.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/tsukuba_l.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/logo_in_clutter.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/pic1.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/pic2.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/pic6.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/pic3.png"
    "/home/saratt/Documents/openML/src/util/opencv/samples/cpp/letter-recognition.data"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

