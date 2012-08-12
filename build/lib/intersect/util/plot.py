# matlab style plotting 
import matplotlib.pyplot as plt

def plot(data, xlb="x axis", ylb="y axis"):
  plt.plot(data)
  plt.ylabel(ylb)
  plt.xlabel(xlb)
  plt.show()


