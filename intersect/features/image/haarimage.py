import cv

#haarNose = cv.Load('src/util/opencv/data/haarcascades/haarcascade_mcs_nose.xml')

numFaces = 1

class Driver:
  
  def __init__(self):

    self.haarCascadeUri = {}
    self.haarCascadeUri['haarcascade_eye_tree_eyeglasses'] = 'src/util/opencv/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml'
    self.haarCascadeUri['haarcascade_eye'] = 'src/util/opencv/data/haarcascades/haarcascade_eye.xml'
    self.haarCascadeUri['haarcascade_frontalface_alt2'] = 'src/util/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml'
    self.haarCascadeUri['haarcascade_frontalface_alt_tree'] = 'src/util/opencv/data/haarcascades/haarcascade_frontalface_alt_tree.xml'
    self.haarCascadeUri['haarcascade_frontalface_alt'] = 'src/util/opencv/data/haarcascades/haarcascade_frontalface_alt.xml'
    self.haarCascadeUri['haarcascade_frontalface_default'] = 'src/util/opencv/data/haarcascades/haarcascade_frontalface_default.xml'
    self.haarCascadeUri['haarcascade_fullbody'] = 'src/util/opencv/data/haarcascades/haarcascade_fullbody.xml'
    self.haarCascadeUri['haarcascade_lefteye_2splits'] = 'src/util/opencv/data/haarcascades/haarcascade_lefteye_2splits.xml'
    self.haarCascadeUri['haarcascade_lowerbody'] = 'src/util/opencv/data/haarcascades/haarcascade_lowerbody.xml'
    self.haarCascadeUri['haarcascade_mcs_eyepair_big'] = 'src/util/opencv/data/haarcascades/haarcascade_mcs_eyepair_big.xml'
    self.haarCascadeUri['haarcascade_mcs_eyepair_small'] = 'src/util/opencv/data/haarcascades/haarcascade_mcs_eyepair_small.xml'
    self.haarCascadeUri['haarcascade_mcs_nose'] = 'src/util/opencv/data/haarcascades/haarcascade_mcs_nose.xml'
    self.haarCascadeUri['haarcascade_mcs_lefteye'] = 'src/util/opencv/data/haarcascades/haarcascade_mcs_lefteye.xml'

    self.cascadeList = []

  def selectCascades(self, cascadeLst):

    print "Cascades Used:"
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

    while frame_index == 0:
      #global detectedObjects
      #global frame

      frame = cv.QueryFrame(camera)

      for cascade in self.cascadeList:
        if frame_index % cascade.getDownsamplingFactor() == 0:
          detectedObjects = cv.HaarDetectObjects(frame, cascade.getCascade(), storage)
          if detectedObjects:
            cascade.setDetectedObjects(detectedObjects)

        detectedObjects = cascade.getDetectedObjects()
        if detectedObjects:
          for face in cascade.getDetectedObjects():
            cv.Rectangle(frame,(face[0][0],face[0][1]),
                           (face[0][0]+face[0][2],face[0][1]+face[0][3]),
                           cascade.getColor(),2)
  
      cv.ShowImage("live", frame)
      c = cv.WaitKey()

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
    self.detectedObjects = None
    self.visible = True
    self.extrapolationLevel = 0
    self.objectBuffer = []
    self.maxBufferLength = 10

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

class haarcascade_frontalface_alt_tree(haarcascade):
  def __init__(self, cscde, nme):
    haarcascade.__init__(self, cscde, nme)
    self.downsamplingFactor = 15
    self.visible = True

    





