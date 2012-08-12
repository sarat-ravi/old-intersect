import cv
import imp
import os

from featureExtractors.video import haarvideo
from featureExtractors.image import haarimage
from featureExtractors.text import nlp


#a.test()

class FeatureExtractor:
  def __init__(self):
    pass

class VideoFeatureExtractor(FeatureExtractor):
  def test(self):
    a = haarvideo.driver()
    a.display_available_actions()
    a.select_actions(['haarcascade_mcs_nose'])
    a.seeCascadesLive()


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

b.test()
a.test()
