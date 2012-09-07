#!/usr/bin/env python
#
# Example for a wavelet analysis
# Authors: Pierre Schnizer
# Date:    October 2006
# 
# To use the same numerical array package as pygsl.
# I only use it here, so not to import a package not installed on the user
# side. Normaly I directly import the array package I use for all my scripts
# and programs.
# There are subtle differences between the packages, thus I would be careful
# which I use in my scripts. 
from pygsl import _numobj as numx
from pygsl import wavelet, errors
import pylab

def transform(data):
    w = wavelet.daubechies(4)
    # If no workspace is given, the wrapper will allocate one itself for the
    # transform. I am not sure how much of an performance impact that is.    
    result = w.transform_forward(data);

    # If you perfer you could have the workspace and the transform stored
    # somewhere, and then perhaps your code is faster
    # work = wavelet.wavelet_workspace(n)
    # result = w.transform_forward(data, work)
    return result

def compress(data):
    n = len(data)
    #w = wavelet.daubechies(4)
    #w = wavelet.daubechies(6)
    #w = wavelet.daubechies(8)
    #w = wavelet.daubechies(10)
    #w = wavelet.daubechies(12)
    #w = wavelet.daubechies(14)
    #w = wavelet.daubechies(16)
    #w = wavelet.daubechies(18)
    #w = wavelet.daubechies_centered(20)
    #w = wavelet.haar(2)
    w = wavelet.bspline(103)
    w = wavelet.bspline(309)
    wavefreq = w.transform_forward(data);
    wavefreqred = numx.zeros(wavefreq.shape, wavefreq.dtype)
    cutfreq = 16
    wavefreqred[:cutfreq] = wavefreq[:cutfreq]
    resampled = w.transform_inverse(wavefreqred)
    return wavefreq, resampled

def searchdim():
    max = 5000
    name = "bspline"
    #name = "bspline_centered"
    #name = "haar"
    #name = "haar_centered"
    #name = "daubechies"
    #name = "daubechies_centered"
    waveletform = getattr(wavelet, name)
    print waveletform
    for i in range(1, max):
        try:
            waveletform(i)
        except errors.gsl_InvalidArgumentError, des:
            continue
        print "Found %s\t dimension\t %d" % (name, i)
        
def run():    
    # Here should go some meaningful data sample to test the transform.
    # Can you write one?
    n = 512
    data = numx.zeros((n,))
    x = numx.arange(n) * (2 * numx.pi / n)
    y = numx.cos(x*5)
    #result = transform(y)

    wavefreq, resampled = compress(y)

    pylab.figure(1)
    pylab.hold(0)
    pylab.plot(x,y,x,resampled)
    pylab.grid(1)
    
    pylab.figure(2)
    pylab.hold(0)
    pylab.plot(wavefreq[:30], '.-')
    pylab.grid(1)

    pylab.figure(3)
    pylab.hold(0)
    pylab.plot(wavefreq[:50], '.-')
    pylab.grid(1)


def singlefreq():
    n = 4096
    data = numx.zeros((n,))
    w = wavelet.bspline_centered(208)
    #w = wavelet.bspline_centered(309)
    #w = wavelet.haar(2)
    #w = wavelet.daubechies_centered(20)
    #w = wavelet.daubechies_centered(4)
    #w = wavelet.daubechies_centered(20)
    
    plots = []
    labels = []
    m = 8
    for i in range(m):
        data[i] = 1

        #fw = w.transform_forward(data)
        iv = w.transform_inverse(data)
        labels.append( "%d" % (i,))
        plots.extend([iv, '-'])
        
    #pylab.figure(1)
    #pylab.hold(0)
    #pylab.plot(data, '.-')

    pylab.figure(2)
    pylab.hold(0)
    pylab.plot(*plots)
    pylab.legend(labels)
    
if __name__ == '__main__':
    run()
