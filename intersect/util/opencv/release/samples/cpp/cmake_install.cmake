# Install script for directory: /Users/saratt/Documents/openML/src/util/opencv/samples/cpp

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/opencv/samples/cpp" TYPE FILE PERMISSIONS OWNER_READ GROUP_READ WORLD_READ FILES
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/3calibration.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/bagofwords_classification.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/bgfg_segm.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/brief_match_test.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/build3dmodel.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/calibration.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/calibration_artificial.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/camshiftdemo.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/chamfer.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/connected_components.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/contours2.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/convexhull.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/cout_mat.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/delaunay2.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/demhist.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/descriptor_extractor_matcher.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/detection_based_tracker_sample.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/detector_descriptor_evaluation.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/detector_descriptor_matcher_evaluation.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/dft.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/distrans.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/drawing.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/edge.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/em.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/facerec_demo.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/fback.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/ffilldemo.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/filestorage.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/fitellipse.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/gencolors.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/generic_descriptor_match.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/grabcut.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/houghcircles.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/houghlines.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/hybridtrackingsample.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/image.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/imagelist_creator.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/inpaint.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/kalman.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/kmeans.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/laplace.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/latentsvm_multidetect.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/letter_recog.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/linemod.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/lkdemo.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/logpolar_bsm.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/matcher_simple.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/matching_to_many_images.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/meanshift_segmentation.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/minarea.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/morphology2.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/multicascadeclassifier.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/opencv_version.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/OpenEXRimages_HighDynamicRange_Retina_toneMapping.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/OpenEXRimages_HighDynamicRange_Retina_toneMapping_video.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/openni_capture.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/peopledetect.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/phase_corr.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/point_cloud.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/points_classifier.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/retinaDemo.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/rgbdodometry.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/segment_objects.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/select3dobj.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/squares.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/starter_imagelist.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/starter_video.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/stereo_calib.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/stereo_match.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/stitching.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/stitching_detailed.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/video_dmtx.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/video_homography.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/videostab.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/watershed.cpp"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/baboon.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/board.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/building.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/fruits.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left01.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left02.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left03.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left04.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left05.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left06.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left07.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left08.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left09.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left11.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left12.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left13.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/left14.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/lena.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right01.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right02.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right03.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right04.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right05.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right06.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right07.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right08.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right09.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right11.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right12.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right13.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/right14.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/stuff.jpg"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/logo.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/logo_in_clutter.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/pic1.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/pic2.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/pic3.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/pic4.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/pic5.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/pic6.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/tsukuba_l.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/tsukuba_r.png"
    "/Users/saratt/Documents/openML/src/util/opencv/samples/cpp/letter-recognition.data"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

