import util

class runningAccuracyCalculator:
  "collects running stats such as accuracy, success rate, min, max, etc."
  def __init__(self):
    self.success_rate = 0
    self.error_rate = 0
    self.num_success = 0
    self.total = 0
    self.num_failure = 0
    self.num_iterations = 0

  def success(self, num_success=1):
    self.num_success += num_success
    self.total += 1
    self.successRate()

  def failure(self, num_failure=1):
    self.num_failure += num_failure
    self.total += 1
    self.errorRate()

  def errorRate(self):
    if self.total == 0:
      return 0
    else:
      self.error_rate = float(self.num_failure)/self.total
      return self.error_rate

  def successRate(self):
    if self.total == 0:
      return 0
    else:
      self.success_rate = 1 - self.errorRate()
      return self.success_rate
