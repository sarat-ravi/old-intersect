import os
import subprocess
from subprocess import call

absPath = os.path.dirname(os.path.abspath(__file__)) + '/'

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

class NlpCLI:

  def __init__(self):
    self.blah = "blah"
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
    print "Shell Output: "
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


class SentenceDetector(NlpCLI):

  def run(self):
    if self.inputFile:
      cmd = opennlp + " SentenceDetector " + models["en-sent.bin"] + " < " + absPath + self.inputFile 
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


class Tokenizer(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " TokenizerME " + models["en-token.bin"] + " < " + absPath + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")


class NameFinder(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " TokenNameFinder " + models["en-ner-person.bin"] + " < " + absPath + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")

class PosTagger(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " POSTagger " + models["en-pos-maxent.bin"] + " < " + absPath + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")

class Chunker(NlpCLI):
  
  def run(self):
    if self.inputFile:
      cmd = opennlp + " ChunkerME " + models["en-chunker.bin"] + " < " + absPath + self.inputFile 
      self.shellOutput = subprocess.check_output(cmd, shell=True)
      f = lambda x: x != ""
      self.lines = filter(f,self.shellOutput.split('\n'))
    else:
      raise Exception("Input file not specified. Call setInputFile('<filepath>')")


  


