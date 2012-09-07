import pygsl
import pygsl.interpolation
numx = pygsl._numobj


n = 10
a = numx.arange(n) * 1.
b = numx.arange(n) * 1.
c = numx.arange(n/2) * 1.

intp = pygsl.interpolation.linear(n)
#pygsl.set_debug_level(10)
intp.init(a,b)
intp.init(a,c)
