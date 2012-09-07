#include <Python.h>

#if (!defined  PyGSL_NUMERIC) && (! defined PyGSL_NUMARRAY)
#error "Neither numarray nor numeric is defined!"
#endif


#ifdef PyGSL_NUMERIC

#define PyArrayObject          PyGSL_Numpy_ArrayObject
/*
#define PyArray_SIZE           PyGSL_Numpy_PyArray_SIZE	    
#define PyArray_NBYTES	       PyGSL_Numpy_PyArray_NBYTES	    
#define PyArray_ISCONTIGUOUS   PyGSL_Numpy_PyArray_ISCONTIGUOUS
#define PyArray_ISSPACESAVER   PyGSL_Numpy_PyArray_ISSPACESAVER
#define SAVESPACE              PyGSL_Numpy_SAVESPACE    
#define SAVESPACEBIT	       PyGSL_Numpy_SAVESPACEBIT 
*/
#define PyArray_Descr	       PyGSL_Numpy_PyArray_Descr

#define PyArray_TYPES          PyGSL_Numpy_TYPES
#define PyArray_CHAR           PyGSL_Numpy_PyArray_CHAR 
#define PyArray_UBYTE          PyGSL_Numpy_PyArray_UBYTE 
#define PyArray_SBYTE          PyGSL_Numpy_PyArray_SBYTE
#define PyArray_SHORT          PyGSL_Numpy_PyArray_SHORT 
#define PyArray_USHORT         PyGSL_Numpy_PyArray_USHORT
#define PyArray_INT            PyGSL_Numpy_PyArray_INT 
#define PyArray_UINT           PyGSL_Numpy_PyArray_UINT
#define PyArray_LONG           PyGSL_Numpy_PyArray_LONG
#define PyArray_FLOAT          PyGSL_Numpy_PyArray_FLOAT 
#define PyArray_DOUBLE         PyGSL_Numpy_PyArray_DOUBLE
#define PyArray_CFLOAT         PyGSL_Numpy_PyArray_CFLOAT 
#define PyArray_CDOUBLE        PyGSL_Numpy_PyArray_CDOUBLE
#define PyArray_OBJECT         PyGSL_Numpy_PyArray_OBJECT
#define PyArray_NTYPES         PyGSL_Numpy_PyArray_NTYPES 
#define PyArray_NOTYPE         PyGSL_Numpy_PyArray_NOTYPE

#include <Numeric/arrayobject.h>

#undef PyArrayObject         
#undef PyArray_SIZE          
#undef PyArray_NBYTES	      
#undef PyArray_ISCONTIGUOUS  
#undef PyArray_ISSPACESAVER  
#undef SAVESPACE             
#undef SAVESPACEBIT	      
#undef PyArray_Descr	      

#undef PyArray_TYPES         
#undef PyArray_CHAR          
#undef PyArray_UBYTE         
#undef PyArray_SBYTE         
#undef PyArray_SHORT         
#undef PyArray_USHORT        
#undef PyArray_INT           
#undef PyArray_UINT          
#undef PyArray_LONG          
#undef PyArray_FLOAT         
#undef PyArray_DOUBLE        
#undef PyArray_CFLOAT        
#undef PyArray_CDOUBLE       
#undef PyArray_OBJECT        
#undef PyArray_NTYPES        
#undef PyArray_NOTYPE        

#endif /* PyGSL_NUMERIC */

#ifdef PyGSL_NUMARRAY
#define PyArrayObject          PyGSL_numarray_ArrayObject
/*

#define PyArray_SIZE           PyGSL_numarray_PyArray_SIZE	    
#define PyArray_NBYTES	       PyGSL_numarray_PyArray_NBYTES	    
#define PyArray_ISCONTIGUOUS   PyGSL_numarray_PyArray_ISCONTIGUOUS
#define PyArray_ISSPACESAVER   PyGSL_numarray_PyArray_ISSPACESAVER
#define SAVESPACE              PyGSL_numarray_SAVESPACE    
#define SAVESPACEBIT	       PyGSL_numarray_SAVESPACEBIT 
#define PyArray_Descr	       PyGSL_numarray_PyArray_Descr
*/
#define PyArray_TYPES          PyGSL_numarray_TYPES
#define PyArray_CHAR           PyGSL_numarray_PyArray_CHAR 
#define PyArray_UBYTE          PyGSL_numarray_PyArray_UBYTE 
#define PyArray_SBYTE          PyGSL_numarray_PyArray_SBYTE
#define PyArray_SHORT          PyGSL_numarray_PyArray_SHORT 
#define PyArray_USHORT         PyGSL_numarray_PyArray_USHORT
#define PyArray_INT            PyGSL_numarray_PyArray_INT 
#define PyArray_UINT           PyGSL_numarray_PyArray_UINT
#define PyArray_LONG           PyGSL_numarray_PyArray_LONG
#define PyArray_FLOAT          PyGSL_numarray_PyArray_FLOAT 
#define PyArray_DOUBLE         PyGSL_numarray_PyArray_DOUBLE
#define PyArray_CFLOAT         PyGSL_numarray_PyArray_CFLOAT 
#define PyArray_CDOUBLE        PyGSL_numarray_PyArray_CDOUBLE
#define PyArray_OBJECT         PyGSL_numarray_PyArray_OBJECT
#define PyArray_NTYPES         PyGSL_numarray_PyArray_NTYPES 
#define PyArray_NOTYPE         PyGSL_numarray_PyArray_NOTYPE

#include <numarray/libnumarray.h>
#undef PyArrayObject         
#undef PyArray_SIZE          
#undef PyArray_NBYTES	      
#undef PyArray_ISCONTIGUOUS  
#undef PyArray_ISSPACESAVER  
#undef SAVESPACE             
#undef SAVESPACEBIT	      
#undef PyArray_Descr	      
#undef PyArray_TYPES         
#undef PyArray_CHAR          
#undef PyArray_UBYTE         
#undef PyArray_SBYTE         
#undef PyArray_SHORT         
#undef PyArray_USHORT        
#undef PyArray_INT           
#undef PyArray_UINT          
#undef PyArray_LONG          
#undef PyArray_FLOAT         
#undef PyArray_DOUBLE        
#undef PyArray_CFLOAT        
#undef PyArray_CDOUBLE       
#undef PyArray_OBJECT        
#undef PyArray_NTYPES        
#undef PyArray_NOTYPE        



#endif  /* PyGSL_NUMARRAY */

#ifdef PyGSL_NUMERIC
#define PyGSL_IS_NUMPY(ob)  PyArray_Check((ob))
#else 
#define PyGSL_IS_NUMPY(ob) (0)
#endif  

#ifdef PyGSL_NUMARRAY
#define PyGSL_IS_NUMARRAY(ob) NA_NumArrayCheck((ob))
#else 
#define PyGSL_IS_NUMARRAY(ob) (0)
#endif

/*
 * Returns which type of conversion to use.
 *
 * 1 ... use numarray
 * 2 ... use numpy
 */
enum {
     PyGSL_NUMARRAY_CONVERSION = 0,
     PyGSL_NUMPY_CONVERSION,     
};

#define PyGSL_DEFAULT_CONVERSION PyGSL_NUMARRAY_CONVERSION
#define PyGSL_NUMX(ob) \
     (\
       (PyGSL_IS_NUMARRAY((ob))) \
     ? \
       PyGSL_NUMARRAY_CONVERSION \
     : \
       (\
	(PyGSL_IS_NUMPY((ob))) \
       ? \
         PyGSL_NUMPY_CONVERSION \
       : \
	 PyGSL_DEFAULT_CONVERSION \
       )\
    )
