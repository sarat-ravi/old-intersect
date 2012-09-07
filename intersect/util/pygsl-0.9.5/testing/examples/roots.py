# Author : Pierre Schnizer
"""
The python equivalent of the C example found in the GSL Reference document.

The function run_fsolver shows how to use the fsolvers (e.g. brent) and the
function run_fdfsolver explains the usage of the fdfsolvers (e.g. newton).
"""
import pygsl
#pygsl.set_debug_level(10)
from pygsl.testing import  roots
import pygsl._numobj as Numeric

def quadratic(x, params):
    a = params[0]
    b = params[1]
    c = params[2]
    tmp =  a * x ** 2 + b * x + c 
    return tmp

def quadratic_deriv(x, params):
    a = params[0]
    b = params[1]
    c = params[2]
    dy= 2.0 * a * x + b
    return dy

def quadratic_fdf(x, params):
    y = quadratic(x, params)
    dy = quadratic_deriv(x, params)
    return y , dy



def run_fsolver():
    a = 1.0
    b = 0.0
    c = -5.0
    solver = roots.brent()
    #solver = roots.bisection()
    #solver = roots.falsepos()
    
    solver.set(quadratic, 0.0, 5, -5.0, (a,b,c))
    iter = 0
    r_expected = Numeric.sqrt(5.0)
    print "# Using solver ", solver.name() 
    print "# %5s [%9s %9s]  %9s  %10s %9s" % ("iter", "upper", "lower", "root",
                                              "err", "err(est)")
    for iter in range(100):           
        status = solver.iterate()
        x_lo = solver.x_lower()
        x_up = solver.x_upper()
        status = solver.test_interval(0, 0.001)
        r = solver.root()
        if status == 0:
            print "#  Convereged :"
        print "  %5d [%.7f %.7f]  %.7f  % .6f % .6f" %(iter, x_lo, x_up, r,
                                                       r -r_expected,
                                                       x_up - x_lo)
        if status == 0:
            break
    else:
        raise ValueError, "Exeeded maximum number of iterations!"

def run_fdfsolver():    
    a = 1.0
    b = 0.0
    c = -5.0
    solver = roots.newton()    
    #solver = roots.secant()
    #solver = roots.steffenson()

    x = 5.0
    
    solver.set(quadratic, quadratic_deriv, quadratic_fdf, x, (a,b,c))
    r_expected = Numeric.sqrt(5.0)
    print "# Using solver ", solver.name() 
    print "# %5s %9s  %10s %9s" % ("iter", "root", "err", "err(est)")
    ok = 1
    for iter in range(10):
        status = solver.iterate()
        x0 = x
        x = solver.root()
        status = roots.test_delta(x, x0, 0.0, 1e-3)
        r = solver.root()
        if status == 0:
            print "#  Convereged :"
        print "%5d  %.7f  % .6f % .6f" %(iter, r, r -r_expected, x - x0)
        if status == 0:
                break
    else:
        raise ValueError, "Exeeded maximum number of iterations!"

if __name__ == '__main__':
    run_fsolver()
    run_fdfsolver()
