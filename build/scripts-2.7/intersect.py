import cv
import imp
import os

from featureExtractors.video import haarvideo
from featureExtractors.image import haarimage
from featureExtractors.text import nlp

#a = haarvideo.driver()
#a.display_available_cascades()
#a.selectCascades(['haarcascade_mcs_nose'])
#a.seeCascadesLive()

#a.test()

driver = nlp.driver()

driver.display_available_actions()
driver.select_actions(["en_sent", "en_ner_person"])
driver.run_actions(input_file="testfiles/input.txt", output_file="testfiles/output.txt", buffer_file="testfiles/buffer.txt", debug=True)

