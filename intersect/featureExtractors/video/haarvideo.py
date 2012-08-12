import cv
import os
#import src.util.dataStructures as dataStructures

absPath = os.path.dirname(os.path.abspath(__file__)) + '/'
STORAGE = cv.CreateMemStorage()

#haarNose = cv.Load(absPath + '../../opencv/data/haarcascades/haarcascade_mcs_nose.xml')

numFaces = 1

class driver:
  
  def __init__(self):

    self.haarCascadeUri = {}
    self.haarCascadeUri['haarcascade_eye_tree_eyeglasses'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml'
    self.haarCascadeUri['haarcascade_eye'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_eye.xml'
    self.haarCascadeUri['haarcascade_frontalface_alt2'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml'
    self.haarCascadeUri['haarcascade_frontalface_alt_tree'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_frontalface_alt_tree.xml'
    self.haarCascadeUri['haarcascade_frontalface_alt'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_frontalface_alt.xml'
    self.haarCascadeUri['haarcascade_frontalface_default'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_frontalface_default.xml'
    self.haarCascadeUri['haarcascade_fullbody'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_fullbody.xml'
    self.haarCascadeUri['haarcascade_lefteye_2splits'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_lefteye_2splits.xml'
    self.haarCascadeUri['haarcascade_lowerbody'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_lowerbody.xml'
    self.haarCascadeUri['haarcascade_mcs_eyepair_big'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_mcs_eyepair_big.xml'
    self.haarCascadeUri['haarcascade_mcs_eyepair_small'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_mcs_eyepair_small.xml'
    self.haarCascadeUri['haarcascade_mcs_nose'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_mcs_nose.xml'
    self.haarCascadeUri['haarcascade_mcs_lefteye'] = absPath + '../../util/opencv/data/haarcascades/haarcascade_mcs_lefteye.xml'

    self.cascadeList = []

  def display_available_actions(self):
    
    print '''
    Available Cascades:
    ---------------------------------
    haarcascade_eye_tree_eyeglasses
    haarcascade_eye
    haarcascade_frontalface_alt2
    haarcascade_frontalface_alt_tree
    haarcascade_frontalface_alt
    haarcascade_frontalface_default
    haarcascade_fullbody
    haarcascade_lefteye_2splits
    haarcascade_lowerbody
    haarcascade_mcs_eyepair_big
    haarcascade_mcs_eyepair_small
    haarcascade_mcs_nose
    haarcascade_mcs_lefteye
    ---------------------------------
    '''

  def select_actions(self, cascadeLst):

    print self.haarCascadeUri['haarcascade_eye']
    print "Actions Selected:"
    print "------------------------"

    for cascade in cascadeLst:
      print cascade
      loadedCascade = cv.Load(str(self.haarCascadeUri[cascade]))
      self.cascadeList.append(self.getHaarCascade(loadedCascade, cascade))

    print "------------------------"

  def test(self):
    print "cascadeUri: "
    print self.haarCascadeUri['haarcascade_eye']

  def seeCascadesLive(self):
    frame_index = 0
    camera = cv.CaptureFromCAM(-1)
    storage = cv.CreateMemStorage()
    cv.NamedWindow("live",cv.CV_WINDOW_AUTOSIZE)

    #frame = None
    #detectedObjects = {}

    while True:
      #global detectedObjects
      #global frame

      frame = cv.QueryFrame(camera)

      for cascade in self.cascadeList:
        cascade.detect_objects(frame)

      for cascade in self.cascadeList:
        frame = cascade.draw_detected_objects_to_frame(frame)

  
      cv.ShowImage("live", frame)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      c = cv.WaitKey(1)
      

      frame_index += 1

  def getHaarCascade(self, loadedCascade, cascadeName):

    haar = None
    try:
      haar = eval(cascadeName + '(loadedCascade, cascadeName)')
    except:
      haar = haarcascade(loadedCascade, cascadeName)

    return haar


class haarcascade:
  def __init__(self, cscde, nme):
    self.cascade = cscde
    self.downsamplingFactor = 1
    self.color = cv.RGB(255,0,0)
    self.name = nme
    self.frame_index = 0
    # all the detected stuff with frame_index as the key
    self.detected_objects_list = {}
    
    # a rectangle, defined by something that cv understands 
    self.detectedObjects = None

    self.visible = True
    self.extrapolationLevel = 0
    self.objectBuffer = []
    self.maxBufferLength = 10

  def detect_objects(self, frame):
    self.frame_index += 1
    if self.frame_index % self.getDownsamplingFactor() == 0:
      detectedObjects = cv.HaarDetectObjects(frame, self.getCascade(), STORAGE)
      if detectedObjects:
        self.setDetectedObjects(detectedObjects)

    self.detected_objects_list[self.frame_index] = self.getDetectedObjects()

  def draw_detected_objects_to_frame(self, frame):
    detectedObjects = self.detected_objects_list[self.frame_index]
    if detectedObjects:
      for face in detectedObjects:
        cv.Rectangle(frame,(face[0][0],face[0][1]),
                       (face[0][0]+face[0][2],face[0][1]+face[0][3]),
                       self.getColor(),2)

    return frame



  def setDetectedObjects(self, val):
    self.detectedObjects = val
    self.extrapolationLevel = 0
    if len(self.objectBuffer) == self.maxBufferLength:
      self.objectBuffer.pop(0)
    self.objectBuffer.append(val)

  

  def getDetectedObjects(self):
  
    if self.visible and len(self.objectBuffer) > 0:

      #insert logic here to smoothen rectangles using buffer data
      
      self.extrapolationLevel += 1
      self.detectedObjects = self.objectBuffer[len(self.objectBuffer) - 1]

      self.filterDetectedObjects()

      return self.detectedObjects

    return None

  def filterDetectedObjects(self):
    #insert logic to filter detectedObjects. I.E. there are only 2 eyes, not 3
    return None


  def setDownsamplingFactor(self, val):
    self.downsamplingFactor = val

  def getDownsamplingFactor(self):
    return self.downsamplingFactor

  def getCascade(self):
    return self.cascade

  def getColor(self):
    return self.color

  def setColor(self, val):
    self.color = val

  def makeVisible(self):
    self.visible = True

  def makeInvisible(self):
    self.visible = False
      

class haarcascade_mcs_nose(haarcascade):
  def __init__(self, cscde, nme):
    haarcascade.__init__(self, cscde, nme)
    self.color = cv.RGB(0,0,255)
    self.downsamplingFactor = 2;

class haarcascade_frontalface_alt_tree(haarcascade):
  def __init__(self, cscde, nme):
    haarcascade.__init__(self, cscde, nme)
    self.downsamplingFactor = 15
    self.visible = True

    





