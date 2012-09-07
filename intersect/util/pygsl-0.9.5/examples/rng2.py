from pygsl import rng
import pygsl
numx = pygsl._numobj

"""
Example of how to use the rng module

Here the usage of the multinomoial distribution and its probability function
is shown.
"""
r = rng.mt19937_1998()
phi = (0.2,0.2,0.2,0.5)  # probability distribution over possible events
                         # (is normalized internally if necessary)

N = 5  # number of trials, that means
       # sum over each row in the samples in 'n'

# sampling 10 data points from the multinomial distribution parametrized
# by 'phi' and 'N'
#pygsl.set_debug_level(10)
n = r.multinomial((N,), (phi,), 10)
print "n = ", n, type(n)



n = r.multinomial((N,), (phi,))
print "n = ", n


p = numx.array([[ 0.9 ,  0.05,  0.05],
                [ 0.05,  0.05,  0.9 ]])

#pygsl.set_debug_level(3)
n = r.multinomial((1,), p, 2)
print "n = ", n


n = r.multinomial((1,), p)
print "n = ", n


n = r.multinomial((1,2), p)
print "n = ", n
