import cv
import os
from util.datastructures import PriorityQueue
#import src.util.dataStructures as dataStructures

absPath = os.path.dirname(os.path.abspath(__file__)) + '/'
STORAGE = cv.CreateMemStorage()

#haarNose = cv.Load(absPath + '../../opencv/data/haarcascades/haarcascade_mcs_nose.xml')

detected_face_objects = []

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

    self.actions = {}

  def display_available_actions(self):
    
    print '''
    Available Actions:
    ---------------------------------
    haarcascade_eye_tree_eyeglasses
    haarcascade_eye
    haarcascade_frontalface_alt2
    haarcascade_frontalface_alt_tree
    haarcascade_frontalface_alt
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

    cascadeLst.insert(0, "haarcascade_frontalface_default")

    for cascade in cascadeLst:
      print cascade
      loadedCascade = cv.Load(str(self.haarCascadeUri[cascade]))
      #self.actions.append(self.getHaarCascade(loadedCascade, cascade))
      self.actions[cascade] = self.getHaarCascade(loadedCascade, cascade)



    print "------------------------"

  def test(self):
    print "cascadeUri: "
    print self.haarCascadeUri['haarcascade_eye']


  class VideoIOHandler:
    def __init__(self, input_file=None, output_file=None, debug=False, display_output=True, save_output=False):
      self.input_file = input_file
      self.output_file = output_file
      self.debug = debug
      self.display_output = display_output
      self.window_name = "live"
      cv.NamedWindow(self.window_name,cv.CV_WINDOW_AUTOSIZE)
      self.save_output = save_output
      self.video_writer = None
      #self.set_video_writer()

    def set_debug(self, dbg):
      self.debug = dbg

    def set_input_file(self, inp):
      if not self.input_file:
        self.input_file = inp

    def set_output_file(self, out):
      if not self.output_file:
        self.output_file = out

    def handle_input(self):
      capture_source = None 

      if not self.input_file:
        capture_source = cv.CaptureFromCAM(-1)
      else:
        capture_source = cv.CaptureFromFile(self.input_file)

      if self.output_file:
        self.set_video_writer(capture_source)

      return capture_source

    def set_video_writer(self, capture):
      #capture = self.handle_input() 
      width =  cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_WIDTH)
      height = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_HEIGHT)
      #frame_size = tuple([width, height])
      fps = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FPS) 
      #fourcc = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FOURCC)
      fourcc = cv.CV_FOURCC('I', '4', '2', '0')

      aviRatio = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_POS_AVI_RATIO)
      framePos = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_POS_FRAMES)
      numFrames = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_COUNT)
      posTime = cv.GetCaptureProperty(capture, cv.CV_CAP_PROP_POS_MSEC)

      #fps = float(fps/100)
      fps = float(fps)
      #print fps
      

      self.video_writer = cv.CreateVideoWriter(self.output_file,int(fourcc), float(fps), (int(width), int(height)), int(1)) 
      #print "video writer initialized"

    def handle_output(self, frame):
      if self.display_output:
        cv.ShowImage(self.window_name, frame)
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

      if self.output_file:
        if self.video_writer:
          cv.WriteFrame(self.video_writer, frame)
        else:
          print "Doing nothing with output because video writer is not initialized"
        




  def run_actions(self, input_file=None, io_handler=None, output_file=None, buffer_file=None, debug=False, display_output=True):
    if not io_handler:
      io_handler = self.VideoIOHandler(input_file=input_file, output_file=output_file, display_output=display_output, debug=debug)

    #io_handler.set_input_file(input_file)
    #io_handler.set_output_file(output_file)
    #io_handler.display_output = display_output
    #io_handler.set_debug(debug)
    capture_source = io_handler.handle_input()
    num_error = 0
    error_tolerance = 1

    while True:
      #global detectedObjects
      #global frame

      if num_error >= error_tolerance:
        break

      frame = cv.QueryFrame(capture_source)
      if not frame:
        #num_error += 1
        print "null frame detected and skipped"
        break
      else:

        for cascade_name, cascade in self.actions.items():
          cascade.detect_objects(frame)

        for cascade_name, cascade in self.actions.items():
          frame = cascade.draw_detected_objects_to_frame(frame)

        io_handler.handle_output(frame)

  def getHaarCascade(self, loadedCascade, cascadeName):

    haar = None
    try:
      haar = eval(cascadeName + '(loadedCascade, cascadeName)')
    except:
      haar = haarcascade(loadedCascade, cascadeName)

    return haar

  def get_action_processor(action_name):

    if action_name in self.actions:
      return self.actions[action_name]
    else:
      raise LookupError("Action '" + action_name + "' is not a valid action")     


class haarcascade:
  def __init__(self, cscde, nme):
    self.cascade = cscde
    self.downsamplingFactor = 1
    self.color = cv.RGB(255,0,0)
    self.name = nme
    self.frame_index = 0
    # all the detected stuff with frame_index as the key
    self.detected_objects_list = {}
    self.max_allowed_objects_per_face = 99999
    self.confidence = 99999 
    self.confidence_threshold = 15
    
    # a rectangle, defined by something that cv understands 
    self.detectedObjects = None

    self.visible = True
    self.extrapolationLevel = 0
    self.objectBuffer = []
    self.maxBufferLength = 10
    self.detectedObjects = None
    self.video_quality_factor = 1.1

  def detect_objects(self, frame):
    self.frame_index += 1
    if self.frame_index % self.getDownsamplingFactor() == 0:
      detectedObjects = cv.HaarDetectObjects(frame, self.cascade, STORAGE, self.video_quality_factor, self.confidence_threshold)
      if detectedObjects:
        self.setDetectedObjects(detectedObjects)

    detected_objects = self.getDetectedObjects()
    self.detected_objects_list[self.frame_index] = detected_objects

  def draw_detected_objects_to_frame(self, frame):
    if self.visible:
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
  
    if len(self.objectBuffer) > 0:

      #insert logic here to smoothen rectangles using buffer data
      
      self.extrapolationLevel += 1
      self.detectedObjects = self.objectBuffer[len(self.objectBuffer) - 1]

      self.filterDetectedObjects()

      return self.detectedObjects

    return None

  def filterDetectedObjects(self):
    #insert logic to filter detectedObjects. I.E. there are only 2 eyes, not 3
    #def remove_low_confidence_objects(detected_obj):
      #if detected_obj[1] < self.confidence_threshold:
        #return None
      #return detected_obj

    #self.detectedObjects = filter(remove_low_confidence_objects, self.detectedObjects)
    pass



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
    self.downsamplingFactor = 2
    self.confidence_threshold = 10
    self.max_allowed_objects_per_face = 1

class haarcascade_eye(haarcascade):
  def __init__(self, cscde, nme):
    haarcascade.__init__(self, cscde, nme)
    self.color = cv.RGB(0,255,255)
    self.downsamplingFactor = 2
    self.confidence_threshold = 20
    self.max_allowed_objects_per_face = 2

class haarcascade_frontalface_default(haarcascade):
  def __init__(self, cscde, nme):
    haarcascade.__init__(self, cscde, nme)
    self.downsamplingFactor = 12
    self.visible = True
    self.color = cv.RGB(0,255,0)

  def detect_objects(self, frame):
    haarcascade.detect_objects(self, frame)
    detected_face_objects = self.detected_objects_list[self.frame_index]
    #if detected_face_objects:
      #print str(detected_face_objects)




    





