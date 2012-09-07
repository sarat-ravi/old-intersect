#!/usr/bin/env python
"""
Illustrate permutation use
"""
from pygsl import permutation
nelements = 5
testfile = "/tmp/permutation2"
p = permutation.Permutation(nelements)
print "Initial Permutation", p.toarray()

p.next()
p.next()
print "Iterated  permutation", p.toarray()
p.write(open(testfile, "w"))



p2 = permutation.Permutation(nelements)
print "New permutation" ,  p2.toarray()
p2.read(open(testfile))
print "After read in", p2.toarray(), "Written was", p.toarray()

