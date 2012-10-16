import cv

im = cv.LoadImageM("sf.jpg", cv.CV_LOAD_IMAGE_GRAYSCALE)
imcolor = cv.LoadImageM("sf.jpg")
(keypoints, descriptors) = cv.ExtractSURF(im, None, cv.CreateMemStorage(), (0, 300, 3, 1))

for ((x, y), laplacian, size, dir, hessian) in keypoints:
    print "x=%d y=%d laplacian=%d size=%d dir=%f hessian=%f" % (x, y, laplacian, size, dir, hessian)
    x = int(x)
    y = int(y)

    center = x, y
    cv.Circle(imcolor, center=center, radius=1, thickness=10, color=cv.RGB(255,0,0))


cv.ShowImage("live", imcolor)
c = cv.WaitKey()
