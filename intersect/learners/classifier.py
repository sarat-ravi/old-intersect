from util.interfaces import DriverInterface

class Driver(DriverInterface):
  
  # Initialize variables here
  def __init__(self):
    raise Exception("__init__ Not Implemented")

  # Display all commands available.
  def display_available_actions(self):
    raise Exception("display_available_actions Not Implemented")

  # takes in one of the commands displayed above as param
  def select_actions(self, actions_array):
    raise Exception("select_actions Not Implemented")

  # Test if the class that inherits this interface implemements all these methods
  def test(self):
    raise Exception("test Not Implemented")

  # run the actions in sequence. If no input file, get from live input (mic/webcam)
  # If no output file, print/display/sound output
  # The IO handler can be overrided by user
  def run_actions(self, io_handler, input_file=None, output_file=None, debug=False):
    raise Exception("run_actions Not Implemented")

  # Get the class instance responsible for handling the action
  def get_action_processor(self):
    raise Exception("get_action_processor Not Implemented")
