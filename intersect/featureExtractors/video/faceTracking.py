#!/usr/bin/env python

import cv
import sys

files = sys.argv[1:]
haarEyes = cv.Load('../../util/opencv/data/haarcascades/haarcascade_eye.xml')
storage = cv.CreateMemStorage()

for f in files:
    capture = cv.CaptureFromFile(f)
    print capture

    width =  cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_WIDTH)
    height = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_HEIGHT)
    #frame_size = tuple([width, height])
    fps = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FPS) 
    fourcc = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FOURCC)

    print "fourcc:"
    print fourcc


    aviRatio = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_POS_AVI_RATIO)
    framePos = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_POS_FRAMES)
    numFrames = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_COUNT)
    posTime = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_POS_MSEC)

    #fps = 20.0
    #print fps
    fps = float(fps/100)

    videoWriter = cv.CreateVideoWriter("output.avi",int(fourcc), float(fps), (int(width), int(height)), int(1)) 

    for i in xrange(10000):
        imcolor = cv.QueryFrame(capture)
        if imcolor:
            #print frame
            percent = float(i/numFrames)
            percent = percent/0.015
            print(percent)
            detectedEyes = cv.HaarDetectObjects(imcolor, haarEyes, storage)
            if detectedEyes:
                for face in detectedEyes:
                    cv.Rectangle(imcolor,(face[0][0],face[0][1]),
                                 (face[0][0]+face[0][2],face[0][1]+face[0][3]),
                                 cv.RGB(155, 55, 200),2)

            #write video
            cv.WriteFrame(videoWriter, imcolor)


            
            
