import pygsl.wavelet as wavelet
import pygsl._numobj as numx

import pygsl

def run(array):
    # Initalise the wavelet and the workspace
    w = wavelet.daubechies(4)
    ws = wavelet.workspace(len(array))
    
    # Transform forward
    result = w.transform_forward(array, ws)

    # Select the largest 20 coefficients
    abscoeff = numx.absolute(result)
    indices  = numx.argsort(abscoeff) # ascending order

    tmp = numx.zeros(result.shape, numx.float_)
    for i in indices[-20:]:
        tmp[i] = result[i] # Set all others to zero

    # And back
    result2 = w.transform_inverse(tmp, ws)

    #print result2
    #print result2 - array
    
if __name__ == '__main__':
    a = numx.arange(256)
    b = numx.sin(a*(2*numx.pi / 16.))
    #b = a * 0.0
    run(b)
