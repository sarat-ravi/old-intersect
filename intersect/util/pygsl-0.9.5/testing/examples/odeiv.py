# Author : Pierre Schnizer
"""
The python equivalent of the C example found in the GSL Reference document.

It prints the calculational ouput to stdout. The first column is t, the
second y[0] and the thrid y[1]. Plot it with your favourite programm to see
the output.

"""
import sys
sys.stdout = sys.stderr
import pygsl._numobj as Numeric
import pygsl
pygsl.set_debug_level(0)
import time
from pygsl.testing import odeiv


def func(t, y, mu):
    f = Numeric.zeros((2,), Numeric.Float) * 1.0
    f[0] = y[1]
    f[1] = -y[0] - mu * y[1] * (y[0] ** 2 -1);
    #f[0] = y[1]
    #f[1] = y[0] * mu
    #print "y", y, "f", f
    return f

def jac(t, y, mu):
    dfdy = Numeric.ones((2,2), Numeric.Float) 
    dfdy[0, 0] = 0.0
    dfdy[0, 1] = 1.0
    dfdy[1, 0] = -2.0 * mu * y[0] * y[1] - 1.0
    dfdy[1, 1] = -mu * (y[0]**2 - 1.0)
    dfdt = Numeric.zeros((2,))
    
    return dfdy, dfdt

def func(t, y, mu):
    f = Numeric.zeros((2,), Numeric.Float) * 1.0
    f[0] = 2 * t
    f[1] = 3 * t**2
    return f

def jac(t, y, mu):
    dfdy = Numeric.ones((2,2), Numeric.Float) 
    dfdy[0, 0] = 0.0
    dfdy[0, 1] = 0.0
    dfdy[1, 0] = 0.0
    dfdy[1, 1] = 0.0
    dfdt = Numeric.zeros((2,))
    dfdt[0] = 2
    dfdt[1] = 3 * 2 * t
    return dfdy, dfdt
    
def run():

    mu = 2.0
    dimension = 2
    # The different possible steppers for the function
    # Comment your favourite one out to test it.
    #stepper = odeiv.step_rk2
    #stepper = odeiv.step_rk4
    #stepper = odeiv.step_rkf45
    #stepper = odeiv.step_rkck
    stepper = odeiv.step_rk8pd
    #stepper = odeiv.step_rk2imp
    #stepper = odeiv.step_rk4imp
    #stepper = odeiv.step_gear1
    #stepper = odeiv.step_gear2
    #stepper = odeiv.step_bsimp
    
    step = stepper(dimension, func, jac, mu)
    # All above steppers exept the odeiv.step_bsimp (Buerlisch - Stoer Improved
    # method can calculate without an jacobian ...
    # step = stepper(dimension, func)

    #print step
    #print step.type()
    
    control = odeiv.control_y_new(step, 1e-6, 1e-6)
    evolve  = odeiv.evolve(step, control)
    print  "# Using stepper %s with order %d" %(step.name(), step.order())
    print  "# Using Control ", control.name()
    print "# %5s %9s %9s  %9s " % ("iter", "t", "y[0]", "y[1]")
    h = 1.
    tstart = 0.0
    t1 = 5
    ystart = (1.0, 0.0)
    
    t = tstart
    y = ystart
    stamp = time.time()
    nsteps = 1000
    for i in xrange(nsteps):
        if t >= t1:
            break

        t, h, y = evolve.apply(t, t1, h, y, mu)
        #print t
	##y = y[-1]
	print "  %5d % 10.6f % 10.6f  % 10.6f " %(i, t, y[0], y[1])
    else:
        raise ValueError, "Maximum number of steps exceeded!"
    print "Needed %f seconds" %( time.time() - stamp,)

    print "  % 10.6f % 10.6f  % 10.6f " %(t, y[0], y[1])
    stamp = time.time()
    #t, h, y = evolve.apply(tstart, t1, h, ystart, nsteps)
    #print "Needed %f seconds" %( time.time() - stamp,)
    #print "  % 10.6f % 10.6f  % 10.6f " %(t, y[0], y[0])


    #print "Evolve"
    #del evolve
    #print "Step"
    #del step
    #print "Control"
    #del control
def run2():
    pygsl.set_debug_level(10)

    x = 2.0
    step = odeiv.step_rk8pd(2, func, None, x)
    control = odeiv.control_y_new(step, 1e-6, 1e-6)
    evolve  = odeiv.evolve(step, control)

    pass

if __name__ == '__main__':
    run()
    #run2()
    
