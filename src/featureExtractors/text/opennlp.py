import opennlpModels
from opennlpModels import SentenceDetector
from opennlpModels import Tokenizer
from opennlpModels import NameFinder

a = NameFinder()
a.setInputFile("tempBuffer/input.txt")
a.run()
a.printOutput()
