import cv
import imp
import os

from features.video import haarvideo
from features.image import haarimage
from features.text import nlp


#a.test()

class FeatureExtractor:
  def __init__(self):
    pass

class VideoFeatureExtractor(FeatureExtractor):
  def test(self):
    a = haarvideo.driver()
    a.display_available_actions()
    a.select_actions(['haarcascade_eye', 'haarcascade_mcs_nose'])
    #a.seeCascadesLive()

    #a.run_actions(input_file="testfiles/input.avi", output_file="testfiles/output.avi", display_output=True)
    #a.run_actions(output_file="testfiles/output.avi", display_output=True)
    a.run_actions(display_output=True)


class TextFeatureExtractor(FeatureExtractor):

  def test(self):

    driver = nlp.driver()

    driver.display_available_actions()
    driver.select_actions(["en_sent", "en_ner_person"])
    driver.run_actions(input_file="testfiles/input.txt", output_file="testfiles/output.txt", buffer_file="testfiles/buffer.txt", debug=True)

    sentDetector = driver.get_action_processor("en_sent")
    #print "Num Sentences: " + str(sentDetector.num_sentences()) + ""

    #print ""

    sentDetector.display_available_methods()

b = TextFeatureExtractor()
a = VideoFeatureExtractor()

#b.test()
a.test()
