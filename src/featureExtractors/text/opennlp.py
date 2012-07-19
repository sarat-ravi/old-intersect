import opennlpModels
from opennlpModels import SentenceDetector
from opennlpModels import Tokenizer
from opennlpModels import NameFinder
from opennlpModels import PosTagger
from opennlpModels import Chunker

a = Chunker()
a.setInputFile("tempBuffer/chunkerInput.txt")
a.run()
a.printOutput()
