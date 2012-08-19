import cv

haarEyes = cv.Load('../../util/opencv/data/haarcascades/haarcascade_eye.xml')
#haarNose = cv.Load('../../util/opencv/data/haarcascades/haarcascade_mcs_nose.xml')

#create window
cv.NamedWindow("w1", cv.CV_WINDOW_AUTOSIZE)

#get camera
camera = cv.CaptureFromCAM(-1) 

storage = cv.CreateMemStorage()

#the index of every frame
frame_index = 0

#one in every 5 frames sent for haar detection
downsamplingFactor = 2

frame = cv.QueryFrame(camera)
detectedEyes = cv.HaarDetectObjects(frame, haarEyes, storage)

def processFrame():
    global detectedEyes

    global frame
    frame = cv.QueryFrame(camera)

    if frame_index % downsamplingFactor == 0:
        temp = cv.HaarDetectObjects(frame, haarEyes, storage)
        if temp:
          detectedEyes = temp

    if True:
        for face in detectedEyes:
            cv.Rectangle(frame,(face[0][0],face[0][1]),
                         (face[0][0]+face[0][2],face[0][1]+face[0][3]),
                         cv.RGB(155, 55, 200),2)

    cv.ShowImage("w1", frame)
    c = cv.WaitKey(1)
    c = cv.WaitKey(1)
    c = cv.WaitKey(1)
    c = cv.WaitKey(1)
    c = cv.WaitKey(1)
    c = cv.WaitKey(1)

while True:
    frame_index = frame_index + 1
    processFrame()
