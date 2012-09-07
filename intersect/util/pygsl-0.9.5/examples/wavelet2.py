#!/usr/bin/env python
#
# Example for a wavelet analysis
# Authors: Fernando Vargas, Pierre Schnizer
# Date:    October 2006
# 
# To use the same numerical array package as pygsl.
# I only use it here, so not to import a package not installed on the user
# side. Normaly I directly import the array package I use for all my scripts
# and programs.
# There are subtle differences between the packages, thus I would be careful
# which I use in my scripts. 
from pygsl import _numobj as numx
from pygsl import wavelet

def transform(data):
    n = len(data)
    w = wavelet.daubechies(4)
    # If no workspace is given, the wrapper will allocate one itself for the
    # transform. I am not sure how much of an performance impact that is.    
    result = w.transform_forward(data);

    # If you perfer you could have the workspace and the transform stored
    # somewhere, and then perhaps your code is faster
    # work = wavelet.wavelet_workspace(n)
    # result = w.transform_forward(data, work)
    return result

def run():    
    # Here should go some meaningful data sample to test the transform.
    # Can you write one?
    n = 512
    data = numx.zeros((n,))

    result = transform(data)
    print result
    
if __name__ == '__main__':
    run()
