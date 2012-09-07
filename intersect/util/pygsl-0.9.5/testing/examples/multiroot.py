# Author : Pierre Schnizer 
"""
The python equivalent of the C example found in the GSL Reference document.

The function run_fsolver shows how to use the fsolvers (e.g. dnewton) and the
function run_fdfsolver explains the usage of the fdfsolvers (e.g. gnewton).
"""
import pygsl
import pygsl._numobj as numx
from pygsl.testing  import multiroot
import copy

def rosenbrock_f(x, params):
    a = params[0]
    b = params[1]
    y = copy.copy(x)
    y[0] = a * (1 - x[0])
    y[1] = b * (x[1] - x[0] * x[0])
    return y

def rosenbrock_df(x, params):
    a = params[0]
    b = params[1]
    df = numx.zeros((x.shape[0], x.shape[0]), numx.Float)
    df[0,0] = -a
    df[0,1] = 0
    df[1,0] = -2 * b * x[0]
    df[1,1] = b
    return df

def rosenbrock_fdf(x, params):
    f = rosenbrock_f(x, params)
    df = rosenbrock_df(x, params)
    return f, df

def run_fsolver():
    params = numx.array((1., 10.), numx.Float)
    
    #solver = multiroots.hybrids(mysys, 2)
    solver = multiroot.dnewton(2)

    tmp = numx.array((-10., -5.), numx.Float)

    solver.set(rosenbrock_f, tmp, params)
    #solver = multiroots.broyden(mysys, 2)
    #solver = multiroots.hybrid(mysys, 2)
    print "# Testing solver ", solver.name(),  solver.type()
    print "# %5s %9s %9s  %9s  %10s" % ("iter", "x[0]", "x[1]", "f[0]", "f[1]")
    for iter in range(100):
        status = solver.iterate()
        x = solver.root()
        dx = solver.dx()
        f = solver.f()
        status = multiroot.test_residual(f, 1e-7)
        if status == 0:
            print "# Converged :"
        print "  %5d % .7f % .7f  % .7f  % .7f" %(iter, x[0], x[1], f[0], f[1])
        if status == 0:
            break
    else:
        raise ValueError, "Number of Iterations exceeded!"

def run_fdfsolver():
    params = numx.array((1., 10.), numx.Float)
    #solver = multiroot.newton(mysys, 2)
    solver = multiroot.gnewton(2)
    #solver = multiroot.hybridj(mysys, 2)
    #solver = multiroot.hybridsj(mysys, 2)
    
    tmp = numx.array((-10., -5.), numx.Float)
    solver.set(rosenbrock_f, rosenbrock_df, rosenbrock_fdf, tmp, params)
    print "# Testing solver ", solver.name(), solver.type()
    print "# %5s %9s %9s  %9s  %10s" % ("iter", "x[0]", "x[1]", "f[0]", "f[1]")
    for iter in range(100):
        status = solver.iterate()
        x = solver.root()
        dx = solver.dx()
        f = solver.f()
        status = multiroot.test_residual(f, 1e-7)
        if status == 0:
            print "# Converged :"
        print "  %5d % .7f % .7f  % .7f  % .7f" %(iter, x[0], x[1], f[0], f[1])
        if status == 0:
            break
    else:
        raise ValueError, "Number of Iterations exceeded!"

if __name__ == '__main__':
    run_fsolver()
    run_fdfsolver()
