import os
import subprocess
from subprocess import call

absPath = os.path.dirname(os.path.abspath(__file__)) + '/'
BUFFER_FILE = absPath + "tempBuffer/output.txt"

#output = subprocess.check_output(["ls","-ltr"])

#array = output.split("\n")
#for sent in array:
  #print sent

opennlp = absPath + "../../util/opennlp_bin/bin/opennlp"

models = {}

models["en-chunker.bin"] = absPath + "../../util/opennlp/models/en-chunker.bin"
models["en-ner-location.bin"] =absPath + "../../util/opennlp/models/en-ner-location.bin"
models["en-ner-money.bin"] = absPath + "../../util/opennlp/models/en-ner-money.bin"
models["en-ner-organization.bin"] = absPath + "../../util/opennlp/models/en-ner-organization.bin"
models["en-ner-percentage.bin"] = absPath + "../../util/opennlp/models/en-ner-percentage.bin"
models["en-ner-person.bin"] = absPath + "../../util/opennlp/models/en-ner-person.bin"
models["en-ner-time.bin"] = absPath + "../../util/opennlp/models/en-ner-time.bin"
models["en-parser-chunking.bin"] = absPath + "../../util/opennlp/models/en-parser-chunking.bin"
models["en-pos-maxent.bin"] = absPath + "../../util/opennlp/models/en-pos-maxent.bin"
models["en-pos-perceptron.bin"] = absPath + "../../util/opennlp/models/en-pos-perceptron.bin"
models["en-sent.bin"] = absPath + "../../util/opennlp/models/en-sent.bin"
models["en-token.bin"] = absPath + "../../util/opennlp/models/en-token.bin"

"""
en-chunker
en-ner-location
en-ner-money
en-ner-organization
en-ner-percentage
en-ner-person
en-ner-time
en-parser-chunking
en-pos-maxent
en-pos-perceptron
en-sent
en-token
"""

class driver:
  
  def __init__(self):
    self.models = models
    self.actions = []

  def display_available_actions(self):
    print """
    en_chunker
    en_ner_person
    en_pos_maxent
    en_sent
    en_token
    """

  def select_actions(self, actionList):
    self.actions = []
    print "Actions Selected:"
    print "------------------------"

    for action in actionList:
      print action
      self.actions.append(self.get_action_processor(action))

    print "------------------------"

  def get_action_processor(self, action):
    action_processor = None
    try:
      action_processor = eval(action + '(' + action + ')')
    except:
      action_processor = None 
      print "Action '" + str(action) + "' failed"

    return action_processor

  def run_actions(self, input_file, output_file, buffer_file=BUFFER_FILE, debug=False):

    index = 0
    last_index = len(self.actions) - 1
    for action in self.actions:
      if index == 0:
        action.setInputFile(input_file)
      else:
        action.setInputFile(buffer_file)

      action.run()
      if debug:
        action.printOutput()
      
      if index == last_index:
        action.writeToFile(output_file)
      else:
        action.writeToFile(buffer_file)

      index += 1


class NlpCLI:

  def __init__(self, action_name):
    self.action_name = action_name
    self.inputFile = None
    self.outputFile = absPath + "tempBuffer/output.txt"
    self.shellOutput = None
    self.lines = None

  def setInputFile(self, inpFile):
    if os.path.isfile(inpFile):
      self.inputFile = inpFile
    else:
      raise Exception("Input file '" + inpFile + "' is not valid")

  def getLines(self):
    if self.lines:
      return self.lines
    else:
      self.run()
      return self.lines

  def setOutputFile(self, outFile):
    self.outputFile = outFile

  def run(self):
    raise Exception("Not Implemented")

  def writeToFile(self,filename):
    if not self.lines:
      self.run()
    outputFile = open(filename, "w")
    for line in self.lines:
      outputFile.write("%s\n" % line)

  def printOutput(self):
    print "" + str(self.action_name) + " output: "
    print "------------------"

    for line in self.lines:
      print line

    print "------------------"


#a = sentenceDetector()
#a.setInputFile("input.txt")
#a.run()
#numSentences = a.numSentences()
##print "num Sentences: "
##print numSentences
#a.printOutput()


class en_sent(NlpCLI):

  def run(self):
    if self.inputFile:
      cmd = opennlp + " SentenceDetector " + models["en-sent.bin"] + " < " + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")

  def numSentences(self):
    if self.lines:
      return len(self.lines)
    else:
      self.run()
      return len(self.lines)


class en_token(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " TokenizerME " + models["en-token.bin"] + " < " + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")


class en_ner_person(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " TokenNameFinder " + models["en-ner-person.bin"] + " < " + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")

class en_pos_maxent(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " POSTagger " + models["en-pos-maxent.bin"] + " < " + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")

class en_chunker(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " ChunkerME " + models["en-chunker.bin"] + " < " + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")
