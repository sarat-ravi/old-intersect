import copy
import sys
import unittest
import pygsl._numobj as Numeric
from pygsl import Float
import pygsl
from pygsl import multiminimize


sys.stdout = sys.stderr

def my_f(v, params):
    x = v[0]
    y = v[1]
    
    dp = params
    t1  = (x - dp[0])
    t2  = (y - dp[1])
    f = 10.0 * t1 * t1 + 20.0 * t2 * t2 + 30.0
    #print "\t\tx,y ->f", x,y, f
    return f 

def my_df(v, params):
    x = v[0]
    y = v[1]
    df = Numeric.zeros(v.shape, Float)
    dp = params
    df[0] = 20. * (x - dp[0])
    df[1] = 40. * (y - dp[1])
    #print "\t\tx,y ->df", x,y, df
    return df

def my_fdf(v, params):
    #print "\t\t-- fdf -- "
    f = my_f(v, params)
    df = my_df(v,params)
    #print "\t\t-- fdf -- "
    return f, df

class FDFTest(unittest.TestCase):
    def _getsize(self):
        return 2

    def _run(self, solver):
        tmp = Numeric.array((5., 7.), Float)
        solver.set(tmp, 0.01, 1e-4)
        #print "Testing solver ", solver.name() 
        #print "%5s %9s %9s  %9s %9s %9s" % ("iter", "x", "y", "f", "dx", "dy")
        for iter in range(200):
            status = solver.iterate()
            gradient = solver.gradient()
            x = solver.getx()
            f = solver.getf()
            status = multiminimize.test_gradient(gradient, 1e-3)
            if status == 0:
                break
            #print "%5d % .7f % .7f  % .7f % .7f % .7f" %(iter, x[0], x[1], f, gradient[0], gradient[1])
        else:
            raise ValueError, "Number of Iterations exceeded!"
        assert(Numeric.absolute(x[0] - 1)<1e-3)
        assert(Numeric.absolute(x[1] - 2)<1e-3)
        assert(Numeric.absolute(f - 30)<1e-3)
        assert(Numeric.absolute(gradient[0])<1e-3)
        assert(Numeric.absolute(gradient[1])<1e-3)
        #print "Minimum found at:"
        #print "%5d % .7f % .7f  % .7f %.7f %.7f" %(iter, x[0], x[1], f, gradient[0], gradient[1])


    def setUp(self):
        tmp = Numeric.array((1., 2.), Float)
        self.sys = multiminimize.gsl_multimin_function_fdf(my_f, my_df, my_fdf, tmp, self._getsize())

    def test_steepest_descent(self):
        solver = multiminimize.steepest_descent(self.sys, self._getsize())
        self._run(solver)

    def test_conjugate_pr(self):
        solver = multiminimize.conjugate_pr(self.sys, self._getsize())
        self._run(solver)

    def test_conjugate_fr(self):
        solver = multiminimize.conjugate_fr(self.sys, self._getsize())
        self._run(solver)

    def test_vector_bfgs(self):
        solver = multiminimize.vector_bfgs(self.sys, self._getsize())
        self._run(solver)

class FTest(unittest.TestCase):
    def _getsize(self):
        return 2

    def setUp(self):
        tmp = Numeric.array((1., 2.), Float)
        self.sys = multiminimize.gsl_multimin_function(my_f, tmp, self._getsize())
    
    def test_nealder_mead(self):
        solver = multiminimize.nmsimplex(self.sys, self._getsize())
        self._run(solver)

    def _run(self, solver):
        start_point = Numeric.array((5., 7.), Float)
        initial_steps = Numeric.array((0.1, 0.1), Float)
        solver.set(start_point, initial_steps)
        
        for i in range(100):
            status = solver.iterate()            
            if status:
                break
            ssval = solver.size()
            rval = multiminimize.test_size (ssval, 1e-2);
     
            #if rval == 0:
            #    print "converged to minimum at"
            fval = solver.getf()
            x = solver.getx()
            t = (i, x[0], x[1], fval, ssval)
            #print "iter %3d x % 10.3e % 10.3e  f() = %-10.3f ssize = %.3f" % t
            if rval == 0:
                break
        else:
            raise ValueError, "Number of Iterations exceeded!"
if __name__ == '__main__':
    unittest.main()
