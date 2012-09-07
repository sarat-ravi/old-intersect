import time
import pygsl.testing.rng as rng
import pygsl.rng as rnga

n_iterations = 20
one_iter = 1000000 * n_iterations
used_time = 0

py_iter = one_iter / 100

myrange = xrange(py_iter)
border = "+%s+" % ("-" * (17 + 3 * (16 +3) + 2))
print border
tmp = ("runs/us", "ns/run") * 3
print "|%-14s| %17s || %17s || %17s |" % (" ","Array", "Py Loop", "Old Impl") 
print "|%-14s| %7s | %7s || %7s | %7s || %7s | %7s |" %( ("Name", ) + tmp)
print border

method = 'landau'
#method = 'get'
for i in rng.types_setup():
    r = rng.rng(getattr(rng, i))
    try:
	ra = getattr(rnga, 'rng_' + i)()
    except AttributeError:
	continue

    call = getattr(r, method)
    t1 = time.clock()
    a = call(one_iter)
    t2 = time.clock()
    used_time = (t2 - t1)
    del a
    t = (r.name(),
         (one_iter * 1.0) / used_time * 1e-6,
         used_time / (one_iter * 1.0) * 1e9)
	 
    call = getattr(r, method)
    l = lambda x: call()
    t1 = time.clock()
    a = map(l, myrange)
    t2 = time.clock()
    used_time = (t2 - t1)
    del a
    t = t + ((py_iter * 1.0) / used_time * 1e-6,
	     used_time / (py_iter * 1.0) * 1e9)	 


    call = getattr(r, method) 
    l = lambda x: call()	     
    t1 = time.clock()
    a = map(l, myrange)
    t2 = time.clock()
    used_time = (t2 - t1)
    del a
    t = t + ((py_iter * 1.0) / used_time * 1e-6,
	     used_time / (py_iter * 1.0) * 1e9)	 
	     
	     
    print "|%-14s| %7.2f | %7.2f || %7.2f | %7.2f || %7.2f | %7.2f |" % t
print border
