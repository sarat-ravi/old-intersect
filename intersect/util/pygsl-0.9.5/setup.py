#! /usr/bin/env python2
#
# author: Achim Gaedke
# created: May 2001
# file: pygsl/setup.py
# $Id: setup.py,v 1.61 2008/10/26 16:37:55 schnizer Exp $
#
# setup script for building and installing pygsl


# Use SWIG to generate the approbriate wrapper files. This is only necessary
# if you modified any interface file as the wrapper files are included in the
# distribution
USE_SWIG = 1

# Some modules have been reimplemented. These modules will be installed in
# pygsl.testing...
# Set to one if you want them built
BUILD_TESTING = 1

# Some modules are not considered to be used in future
BUILD_DEPRECATED = 0

#
# If you want to use the PyGSL API in other projects ...
# Well, I do
#
INSTALL_HEADERS = 1
#
#
#####
# PyGSL comes with a lot of debug information. This can be either disabled
# setting DEBUG_LEVEL to 0 at compile time, swtiched on and off at run time
# using pygsl.set_debug_level(level) setting DEBUG_LEVEL to 0 or set to some
# value during compile time using a level bigger than 1 (the heigher the value
# is the more verbose the output gets. Please note that pygsl needs to be
# completly rebuild if you hcange this parameter
# No debug information
#DEBUG_LEVEL = 0
# dynamic debug information
DEBUG_LEVEL = 1
# Compile time set debug level
#DEBUG_LEVEL = 10
#####
#------------------------------------------------------------------------------
# As long as you are not taking part in the development process, I hope that 
# you do not need to modify anything here.



import sys
import time
import string
import glob

# Add the gsldist path
import os
pygsldir = os.path.dirname("__name__")
# Get the version information
versionfile = open(os.path.join(pygsldir, "pygsl", "_version.py"))
exec(versionfile)

# Make sure that we use the new one ...
gsldist_path = os.path.join(pygsldir, "gsl_dist")
sys.path.insert(0, gsldist_path)

#This must be before gsl_Extension is included.
import gsl_numobj

import distutils
from distutils.core import setup, Extension
from gsl_Extension import gsl_Extension
from swig_extension import SWIG_Extension as _SWIG_Extension
from swig_extension import SWIG_Extension_Nop as _SWIG_Extension_Nop

from distutils import sysconfig
#from common_objects import libpygsl

if USE_SWIG == 0:
    _SWIG_Extension = _SWIG_Extension_Nop

exts = []

def SWIG_Extension(*args, **kws):
    kws["py_dir"] = "pygsl"
    kws["c_dir"] = "swig_src"
    return apply(_SWIG_Extension, args, kws)



check_macros = [('GSL_DISABLE_DEPRECATED', 1)]
macros = [('SWIG_COBJECT_TYPES', 1), ('GSL_RANGE_CHECK', 1)] #+ check_macros
macros = macros + [('DEBUG', DEBUG_LEVEL)]
debug_macros = macros + [('DEBUG', 1)]

pygsl_errno=gsl_Extension("errno",
			 ['src/init/errorno.c'],
                         gsl_min_version=(1,),
                         define_macros = macros,
                         python_min_version=(2,1),
                         )
exts.append(pygsl_errno)
pygsl_init=gsl_Extension("init",
			 ['src/init/initmodule.c'],
                         gsl_min_version=(1,),
                         define_macros = macros,
                         python_min_version=(2,1),
                         )
exts.append(pygsl_init)
pygsl_init=gsl_Extension("inittest",
			 ['src/init/inittestmodule.c'],
                         gsl_min_version=(1,),
                         define_macros = macros,
                         python_min_version=(2,1),
                         )
exts.append(pygsl_init)

exts.append(SWIG_Extension("hankel",                           
                           ["src/hankel/gsl_hankel.i"],
                           swig_include_dirs=["src/hankel"],
                           gsl_min_version=(1,0),
                           define_macros = macros,
                           python_min_version=(2,0),
                          )
            
            )

exts.append(SWIG_Extension("sum",
                          ["src/sum/gsl_sum.i"],
                          gsl_min_version=(1,0),
                          define_macros = macros,
                          python_min_version=(2,0),
                          )
            )
exts.append(SWIG_Extension("bspline",
                           ["src/bspline/bspline.i"],
                           include_dirs=["src/bspline"],
                           swig_include_dirs=["src/bspline"],
                           gsl_min_version=(1,9),
                           define_macros = macros,
                           python_min_version=(2,1),
                          )            
            )

exts.append(SWIG_Extension("_callback",
                           ["src/callback/gsl_callback.i"],
                           include_dirs=["src/callback"],
                           swig_include_dirs=["src/callback"],
                           gsl_min_version=(1,2),
                           define_macros = macros,
                           python_min_version=(2,1),
                          )            
            )

exts.append(SWIG_Extension("callback_function_test",
                           ["src/callback/gsl_function_test.i"],
                           include_dirs=["src/callback"],
                           swig_include_dirs=["src/callback"],
                           gsl_min_version=(1,2),
                           define_macros = macros,
                           python_min_version=(2,1),
                          )
            )

exts.append(SWIG_Extension("_poly",
                          ["src/poly/gsl_poly.i"],
                          include_dirs=["src/poly"],
                          define_macros = macros,
                          gsl_min_version=(1,2),
                          python_min_version=(2,1)
                          )
            )

exts.append(SWIG_Extension("_block",
                          ["src/block/gsl_block.i"],
                           swig_include_dirs=["src/block"],
                          define_macros = macros,
                           gsl_min_version=(1,2),
                          python_min_version=(2,1)
                          )
            )

pygsl_siman=gsl_Extension("_siman",
                          ['src/simanmodule.c'],
                          define_macros = macros,
                          gsl_min_version=(1,2),
                          python_min_version=(2,1)
                          )
exts.append(pygsl_siman)

pygsl_const=gsl_Extension("const",
			  ['src/constmodule.c'],
                          define_macros = macros,
                          gsl_min_version=(1,2),
                          python_min_version=(2,1)
                          )
exts.append(pygsl_const)
if BUILD_DEPRECATED:
    pygsl_diff = gsl_Extension("diff",
                               ['src/diffmodule.c'],
                               define_macros = macros,
                               gsl_min_version=(1,'0+'),
                               python_min_version=(2,1)
                               )
    exts.append(pygsl_diff) 

pygsl_deriv = gsl_Extension("deriv",
                           ['src/derivmodule.c'],
                           define_macros = macros,
                           gsl_min_version=(1, 5),
                           python_min_version=(2,1)
                           )
exts.append(pygsl_deriv)
pygsl_transform = gsl_Extension("_transform",
                           ['src/transform/transformmodule.c'],
                           define_macros = macros,
                           gsl_min_version=(1,'0+'),
                           python_min_version=(2,1)
                           )
exts.append(pygsl_transform)
try:
    pygsl_rng=gsl_Extension("rng",
                            ['src/rng/rngmodule.c'],
                            gsl_min_version=(1,'0+'),
                            define_macros = macros,
                            python_min_version=(2,1)
                         )
    exts.append(pygsl_rng)
    
    
    exts.append(SWIG_Extension("gslwrap",
                              ["src/gslwrap/gsl_gslwrap.i"],
                               swig_include_dirs=["src/gslwrap/"],
                              define_macros = macros,
                              gsl_min_version=(1,10),
                              python_min_version=(2,1)
                              )
                )

    pygsl_ieee=gsl_Extension("ieee",
                             ['src/ieeemodule.c'],
                             gsl_min_version=(1,),
                             define_macros = macros,
                             python_min_version=(2,1)
                             )
    exts.append(pygsl_ieee)
    exts.append(SWIG_Extension("gslwrap",
                              ["src/gslwrap/gsl_gslwrap.i"],
                               swig_include_dirs=["src/gslwrap/"],
                              define_macros = macros,
                              gsl_min_version=(1,2),
                              python_min_version=(2,1)
                              )
                )
    pygsl_histogram=gsl_Extension("histogram",
                                  ['src/histogram/histogrammodule.c'],
                                  define_macros = macros,
                                  gsl_min_version=(1,'0+'),
                                  python_min_version=(2,2)
                                  )
    exts.append(pygsl_histogram)    
    pygsl_multimin=gsl_Extension("multimin",
                                  ['src/multiminmodule.c'],
                                 define_macros = macros,
                                  gsl_min_version=(1,'0+'),
                                  python_min_version=(2,2)
                                  )
    exts.append(pygsl_multimin)    
except distutils.errors.DistutilsExecError:
    pass


pygsl_qrng=gsl_Extension("_qrng",
                         ['src/qrng_module.c'],
                         gsl_min_version=(1,'0+'),
                         define_macros = macros,
                         python_min_version=(2,1)
                         )
exts.append(pygsl_qrng)

pygsl_sf=gsl_Extension("sf",
		       ['src/sfmodule.c'],
		       gsl_min_version=(1,),
                       define_macros = macros,
                       python_min_version=(2,1)
                       )
exts.append(pygsl_sf)
pygsl_statistics_basis=gsl_Extension("statistics._stat",
                                     ['src/statistics/_statmodule.c'],
                                     gsl_min_version=(1,),
                                     define_macros = macros,
                                     python_min_version=(2,1)
                                     )
exts.append(pygsl_statistics_basis)
pygsl_statistics_uchar=gsl_Extension("statistics.uchar",
                                     ['src/statistics/ucharmodule.c'],
                                     gsl_min_version=(1,),
                                     define_macros = macros,
                                     python_min_version=(2,1)
                                     )
exts.append(pygsl_statistics_uchar)    
pygsl_statistics_char=gsl_Extension("statistics.char",
                                    ['src/statistics/charmodule.c'],
                                    gsl_min_version=(1,),
                                    define_macros = macros,
                                    python_min_version=(2,1)
                                    )
exts.append(pygsl_statistics_char)    
pygsl_statistics_double=gsl_Extension("statistics.double",
                                      ['src/statistics/doublemodule.c'],
                                      gsl_min_version=(1,),
                                      define_macros = macros,
                                      python_min_version=(2,1)
                                      )
exts.append(pygsl_statistics_double)    
pygsl_statistics_float=gsl_Extension("statistics.float",
                                     ['src/statistics/floatmodule.c'],
                                     gsl_min_version=(1,),
                                     define_macros = macros,
                                     python_min_version=(2,1)
                                      )
exts.append(pygsl_statistics_float)    
pygsl_statistics_long=gsl_Extension("statistics.long",
                                    ['src/statistics/longmodule.c'],
                                    gsl_min_version=(1,),
                                    define_macros = macros,
                                    python_min_version=(2,1)
                                    )
exts.append(pygsl_statistics_long)    
pygsl_statistics_int=gsl_Extension("statistics.int",
                                   ['src/statistics/intmodule.c'],
                                   gsl_min_version=(1,),
                                   define_macros = macros,
                                   python_min_version=(2,1)
                                   )
exts.append(pygsl_statistics_int)    
pygsl_statistics_short=gsl_Extension("statistics.short",
                                     ['src/statistics/shortmodule.c'],
                                     gsl_min_version=(1,),
                                     define_macros = macros,
                                     python_min_version=(2,1)
                                     )
exts.append(pygsl_statistics_short)    

errortest = gsl_Extension("errortest",
                          ['src/errortestmodule.c'],
                          gsl_min_version=(1,),
                          define_macros = macros,
                          python_min_version=(2,0)
                          )
exts.append(errortest)

if BUILD_DEPRECATED:
    pygsl_matrix=gsl_Extension("matrix",
                               ['src/matrixmodule.c'],
                               define_macros = macros,
                               gsl_min_version=(1,'0+'),
                               python_min_version=(2,2)
                               )
    exts.append(pygsl_matrix)    

if BUILD_TESTING:
    solver=gsl_Extension("testing.multimin",
                         ['testing/src/solvers/multimin.c'],
                         gsl_min_version=(1,),
                         define_macros = macros, 
                         python_min_version=(2,0)
                         )
    exts.append(solver)

    solver=gsl_Extension("testing.multiroot",
                         ['testing/src/solvers/multiroot.c'],
                         gsl_min_version=(1,),
                         define_macros = macros, 
                         python_min_version=(2,0)
                         )
    exts.append(solver)

    solver=gsl_Extension("testing.multifit_nlin",
                         ['testing/src/solvers/multifit_nlin.c'],
                         gsl_min_version=(1,),
                         define_macros = macros, 
                         python_min_version=(2,0)
                         )
    exts.append(solver)

    solver=gsl_Extension("testing.minimize",
                         ['testing/src/solvers/minimize.c'],
                         gsl_min_version=(1,),
                         define_macros = macros, 
                         python_min_version=(2,0)
                         )
    exts.append(solver)

    solver=gsl_Extension("testing.roots",
                         ['testing/src/solvers/roots.c'],
                         gsl_min_version=(1,),
                         define_macros = macros, 
                         python_min_version=(2,0)
                         )
    exts.append(solver)

    solver=gsl_Extension("testing.odeiv",
                         ['testing/src/solvers/odeiv.c'],
                         gsl_min_version=(1,),
                         define_macros = macros, 
                         python_min_version=(2,0)
                         )
    exts.append(solver)

    #solver=gsl_Extension("testing.monte",
    #                     ['testing/src/solvers/monte.c'],
    #                     gsl_min_version=(1,),
    #                     define_macros = macros, 
    #                     python_min_version=(2,0)
    #                     )
    #exts.append(solver)

    solver=gsl_Extension("testing.solver",
                         ['testing/src/solvers/solvermodule.c'],
                         gsl_min_version=(1,),
                         define_macros = macros + [("ONEFILE", 1)],
                         python_min_version=(2,0)
                     )
    exts.append(solver)
    #cheb=gsl_Extension("testing.chebyshev",
    #                     ['testing/src/solvers/chebyshev.c'],
    #                     gsl_min_version=(1,),
    #                     define_macros = macros + [("ONEFILE", 1)],
    #                     python_min_version=(2,0)
    #                 )

    num = str(gsl_numobj.nummodule)
    if num in ("numpy", "Numeric"):
        print "Building testing ufuncs!"
        sfarray=gsl_Extension("testing.sfarray",
                              ['testing/src/sf/sf__arrays.c'],
                              gsl_min_version=(1,),
                              define_macros = macros,
                              python_min_version=(2,0)
                              )
        #exts.append(sfarray)        
        sf=gsl_Extension("testing._ufuncs",
                         ['testing/src/sf/sfmodule_testing.c'],
                         gsl_min_version=(1,),
                         define_macros = macros,
                         python_min_version=(2,0)
                         )
        exts.append(sf)
    else:
        print "Selected array object -->%s<--" % (num,)
        print "No special ufuncs in testing"
    #exts.append(cheb)
    pass

py_module_names = ['errors',
                   'statistics.__init__',
		   '_numobj',
		   '_mlab',
                   '_block',
                   '_callback',
                   '_generic_solver',
                   '_poly',
                   'blas',
                   'block',
                   'chebyshev',
                   'combination',
                   'eigen',
                   'fft',
                   'fit',
                   'gsl_function',
                   'gslwrap',
                   'hankel',
                   'integrate',
                   'interpolation',
                   'linalg',
                   'matrix_pierre',
                   'minimize',
                   'monte',
                   'multifit',
                   'multifit_nlin',
                   'multiroots',
                   'odeiv',
                   'permutation',
                   'poly',
                   'qrng',
                   'roots',
                   'siman',
                   'sum',
                   'spline',
                   'testing.__init__',
                   'vector',
                   'math'
                   ]

gsldist = []
headers = None
if INSTALL_HEADERS == 1:
    headers = glob.glob("Include/pygsl/*.h")
    gsldist = map(lambda x: 'gsl_dist.' + os.path.basename(x)[:-3], glob.glob("gsl_dist/*.py"))

py_modules = map(lambda x : 'pygsl.' + x, py_module_names) + gsldist 
    
extends = ""
if "bdist" in sys.argv:
    extends = "_" + str(gsl_numobj.nummodule)

setup (name = "pygsl",
       version = version + extends,
       #version = "snapshot_" + string.join(map(str, time.gmtime()[:3]), '_'),
       description = "GNU Scientific Library Interface",
       long_description = "This project provides a python interface for the GNU scientific library (gsl)",
       license = "GPL",
       author = "Achim Gaedke, Pierre Schnizer",
       author_email = "AchimGaedke@users.sourceforge.net, schnizer@users.sourceforge.net",
       url = "http://pygsl.sourceforge.net",       
       package_dir = {'pygsl' : 'pygsl', 'pygsl.gsl_dist' : 'gsl_dist'},
       packages = ['pygsl', 'pygsl.testing', 'pygsl.statistics', 'pygsl.gsl_dist'],
       ext_package = 'pygsl',
       ext_modules = exts,
       headers = headers
       )




