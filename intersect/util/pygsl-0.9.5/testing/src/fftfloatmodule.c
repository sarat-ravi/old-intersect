/*
 * Author : Pierre Schnizer
 * Date   : December 2004
 *
 */

/*
#ifdef DEBUG
#undef DEBUG
#endif

#define DEBUG 10
*/

#include <gsl/gsl_fft.h>

#include <gsl/gsl_fft_complex.h>
#include <gsl/gsl_fft_real.h>
#include <gsl/gsl_fft_halfcomplex.h>

#include <gsl/gsl_fft_complex_float.h>
#include <gsl/gsl_fft_real_float.h>
#include <gsl/gsl_fft_halfcomplex_float.h>

#include <pygsl/error_helpers.h>
#include <pygsl/block_helpers.h>

enum pygsl_fft_space_type{
	COMPLEX_WORKSPACE = 0,
	REAL_WORKSPACE,
	COMPLEX_WAVETABLE,
	REAL_WAVETABLE,
	HALFCOMPLEX_WAVETABLE,
	COMPLEX_WORKSPACE_FLOAT,
	REAL_WORKSPACE_FLOAT,
	COMPLEX_WAVETABLE_FLOAT,
	REAL_WAVETABLE_FLOAT,
	HALFCOMPLEX_WAVETABLE_FLOAT
};

enum pygsl_fft_mode{
	MODE_DOUBLE = 0,
	MODE_FLOAT
};

union pygsl_fft_space_t{
	gsl_fft_complex_workspace     *cws;
	gsl_fft_complex_wavetable     *cwt;
	gsl_fft_real_workspace        *rws;
	gsl_fft_real_wavetable        *rwt;
	gsl_fft_halfcomplex_wavetable *hcwt;
	gsl_fft_complex_workspace_float     *cwsf;
	gsl_fft_complex_wavetable_float     *cwtf;
	gsl_fft_real_workspace_float        *rwsf;
	gsl_fft_real_wavetable_float        *rwtf;
	gsl_fft_halfcomplex_wavetable_float *hcwtf;
	void                          *v;
};

typedef struct {
	PyObject_HEAD
	union pygsl_fft_space_t space;
	int type;
} PyGSL_fft_space;

static PyObject *module = NULL;
static const char filename[] = __FILE__;

static const char  PyGSL_fft_space_type_doc[] = "\
A catch all of the various space types of the fft module. Call the method\n\
'get_type' to find what object is wrapped underneath!\n\
";
static void
PyGSL_fft_space_dealloc(PyGSL_fft_space * self);

static PyObject*
PyGSL_fft_space_getattr(PyGSL_fft_space * self, char * name);

#define PyGSL_fft_space_check(op) ((op)->ob_type == &PyGSL_fft_space_pytype)
#define PyGSL_complex_fft_work_space_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == COMPLEX_WORKSPACE)
#define PyGSL_complex_fft_wave_table_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == COMPLEX_WAVETABLE)
#define PyGSL_halfcomplex_fft_wave_table_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == HALFCOMPLEX_WAVETABLE)
#define PyGSL_real_fft_work_space_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == REAL_WORKSPACE)
#define PyGSL_real_fft_wave_table_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == REAL_WAVETABLE)

#define PyGSL_complex_fft_work_space_float_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == COMPLEX_WORKSPACE_FLOAT)
#define PyGSL_complex_fft_wave_table_float_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == COMPLEX_WAVETABLE_FLOAT)
#define PyGSL_halfcomplex_fft_wave_table_float_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == HALFCOMPLEX_WAVETABLE_FLOAT)
#define PyGSL_real_fft_work_space_float_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == REAL_WORKSPACE_FLOAT)
#define PyGSL_real_fft_wave_table_float_check(op) \
         (PyGSL_fft_space_check(op) && ((PyGSL_fft_space *)op)->type == REAL_WAVETABLE_FLOAT)

#define PyGSL_FFT_MODE_SWITCH(mode, double_element, float_element) \
        (mode == MODE_DOUBLE) ? double_element : float_element



PyTypeObject PyGSL_fft_space_pytype = {
  PyObject_HEAD_INIT(NULL)	 /* fix up the type slot in initcrng */
  0,				 /* ob_size */
  "PyGSL_fft_space",		 /* tp_name */
  sizeof(PyGSL_fft_space),	 /* tp_basicsize */
  0,				 /* tp_itemsize */

  /* standard methods */
  (destructor)  PyGSL_fft_space_dealloc, /* tp_dealloc  ref-count==0  */
  (printfunc)   0,		         /* tp_print    "print x"     */
  (getattrfunc) PyGSL_fft_space_getattr,  /* tp_getattr  "x.attr"      */
  (setattrfunc) 0,		 /* tp_setattr  "x.attr=v"    */
  (cmpfunc)     0,		   /* tp_compare  "x > y"       */
  (reprfunc)    0,                 /* tp_repr     `x`, print x  */

  /* type categories */
  0,				/* tp_as_number   +,-,*,/,%,&,>>,pow...*/
  0,				/* tp_as_sequence +,[i],[i:j],len, ...*/
  0,				/* tp_as_mapping  [key], len, ...*/

  /* more methods */
  (hashfunc)     0,		/* tp_hash    "dict[x]" */
  (ternaryfunc)  0,      /* tp_call    "x()"     */
  (reprfunc)     0,             /* tp_str     "str(x)"  */
  (getattrofunc) 0,		/* tp_getattro */
  (setattrofunc) 0,		/* tp_setattro */
  0,				/* tp_as_buffer */
  0L,				/* tp_flags */
  (char *) PyGSL_fft_space_type_doc		/* tp_doc */
};

static PyObject *
PyGSL_fft_space_get_factors(PyGSL_fft_space *self, PyGSL_fft_space *args)
{

       int nf, i;                                                           
       long *data=NULL;
       size_t *cp_data=NULL;
       PyArrayObject * a_array = NULL;					    
									    
       assert(PyGSL_fft_space_check(self));

       DEBUG_MESS(2, "Type = %d", self->type);
       switch(self->type){
       case COMPLEX_WAVETABLE:           nf = self->space.cwt ->nf;  cp_data = self->space.cwt ->factor;  break;
       case REAL_WAVETABLE:	         nf = self->space.rwt ->nf;  cp_data = self->space.rwt ->factor;  break;
       case HALFCOMPLEX_WAVETABLE:       nf = self->space.hcwt->nf;  cp_data = self->space.hcwt->factor;  break;	       
       case COMPLEX_WAVETABLE_FLOAT:     nf = self->space.cwtf ->nf; cp_data = self->space.cwtf ->factor; break;
       case REAL_WAVETABLE_FLOAT:        nf = self->space.rwtf ->nf; cp_data = self->space.rwtf ->factor; break;
       case HALFCOMPLEX_WAVETABLE_FLOAT: nf = self->space.hcwtf->nf; cp_data = self->space.hcwtf->factor; break;	       
       default: gsl_error("Got unknown switch", filename, __LINE__, GSL_ESANITY); return NULL; break;
       }

       assert(nf < 64);
       a_array = (PyArrayObject *) PyGSL_New_Array(1, &nf, PyArray_LONG);
       if(a_array == NULL)
	       return NULL;
       data = (long *) a_array->data;

       
       for(i=0; i<nf; i++){
	    data[i] = (long) cp_data[i];
       }
       return (PyObject *) a_array;

}
static const char PyGSL_fft_space_get_factors_doc[] = " Get the factors ...";
static const char PyGSL_fft_space_get_type_doc[] = " Get the type of this space";

static PyObject *
PyGSL_fft_space_get_type(PyGSL_fft_space *self, PyObject *notused)
{
	char *p = NULL;

	switch(self->type){
	case COMPLEX_WORKSPACE:           p = "COMPLEX_WORKSPACE";           break;
	case REAL_WORKSPACE:	          p = "REAL_WORKSPACE";	             break;
	case COMPLEX_WAVETABLE:           p = "COMPLEX_WAVETABLE";	     break;
	case REAL_WAVETABLE:	          p = "REAL_WAVETABLE";	             break;
	case HALFCOMPLEX_WAVETABLE:       p = "HALFCOMPLEX_WAVETABLE";       break;
	case COMPLEX_WORKSPACE_FLOAT:     p = "COMPLEX_WORKSPACE_FLOAT";     break;
	case REAL_WORKSPACE_FLOAT:	  p = "REAL_WORKSPACE_FLOAT";	     break;
	case COMPLEX_WAVETABLE_FLOAT:     p = "COMPLEX_WAVETABLE_FLOAT";     break;
	case REAL_WAVETABLE_FLOAT:	  p = "REAL_WAVETABLE_FLOAT";	     break;
	case HALFCOMPLEX_WAVETABLE_FLOAT: p = "HALFCOMPLEX_WAVETABLE_FLOAT"; break;
	default: gsl_error("Got unknown switch", filename, __LINE__, GSL_ESANITY); return NULL;
	}
	return PyString_FromString(p);
}

static PyMethodDef PyGSL_fft_wavetable_methods[] = {
	{"get_factors",  (PyCFunction)PyGSL_fft_space_get_factors, METH_NOARGS,  (char *)PyGSL_fft_space_get_factors_doc},
	{"get_type",     (PyCFunction)PyGSL_fft_space_get_type, METH_NOARGS,  (char *)PyGSL_fft_space_get_type_doc},
	{NULL, NULL, 0, NULL}           /* sentinel */
};

static PyMethodDef PyGSL_fft_space_methods[] = {
	{"get_type",     (PyCFunction)PyGSL_fft_space_get_type, METH_NOARGS,  (char *)PyGSL_fft_space_get_type_doc},
	{NULL, NULL, 0, NULL}           /* sentinel */
};

static PyObject*
PyGSL_fft_space_getattr(PyGSL_fft_space *self, char *name)
{
     PyObject *tmp = NULL;
     FUNC_MESS_BEGIN();
     assert(PyGSL_fft_space_check(self));     
     switch(self->type){
     case  COMPLEX_WORKSPACE:
     case  REAL_WORKSPACE:    
     case  COMPLEX_WORKSPACE_FLOAT:
     case  REAL_WORKSPACE_FLOAT:
	     tmp = Py_FindMethod(PyGSL_fft_space_methods, (PyObject *) self, name);
     default:
	     tmp = Py_FindMethod(PyGSL_fft_wavetable_methods, (PyObject *) self, name);
     }
     FUNC_MESS_END();
     return tmp;
}

static void
PyGSL_fft_space_dealloc(PyGSL_fft_space * self)
{
     FUNC_MESS_BEGIN();
     assert(PyGSL_fft_space_check(self));     
     switch(self->type){
     case COMPLEX_WORKSPACE:           gsl_fft_complex_workspace_free(self->space.cws);       break;
     case COMPLEX_WAVETABLE:           gsl_fft_complex_wavetable_free(self->space.cwt);       break;
     case REAL_WORKSPACE:              gsl_fft_real_workspace_free(self->space.rws);          break;
     case REAL_WAVETABLE:	       gsl_fft_real_wavetable_free(self->space.rwt);          break;
     case HALFCOMPLEX_WAVETABLE:       gsl_fft_halfcomplex_wavetable_free(self->space.hcwt);  break;
     case COMPLEX_WORKSPACE_FLOAT:     gsl_fft_complex_workspace_float_free(self->space.cwsf);      break;
     case COMPLEX_WAVETABLE_FLOAT:     gsl_fft_complex_wavetable_float_free(self->space.cwtf);      break;
     case REAL_WORKSPACE_FLOAT:        gsl_fft_real_workspace_float_free(self->space.rwsf);         break;
     case REAL_WAVETABLE_FLOAT:	       gsl_fft_real_wavetable_float_free(self->space.rwtf);         break;
     case HALFCOMPLEX_WAVETABLE_FLOAT: gsl_fft_halfcomplex_wavetable_float_free(self->space.hcwtf); break;
     default: gsl_error("Got unknown switch", filename, __LINE__, GSL_ESANITY); break;
     }
     FUNC_MESS_END();
}

static PyObject* 
PyGSL_fft_space_init(PyObject *self, PyObject *args, int type)
{
	PyGSL_fft_space *o=NULL;
	size_t n;
	o =  (PyGSL_fft_space *) PyObject_NEW(PyGSL_fft_space, &PyGSL_fft_space_pytype);
	if(o == NULL){
		return NULL;
	}

	if (0==PyArg_ParseTuple(args,"l", &n))
		return NULL;


	if (n<=0) {
		PyErr_SetString(PyExc_RuntimeError, "dimension must be >0");
		return NULL;
	}
	o->type = type;
	switch(type){
	case COMPLEX_WORKSPACE:           o->space.cws  = gsl_fft_complex_workspace_alloc(n);            break;
	case COMPLEX_WAVETABLE:           o->space.cwt  = gsl_fft_complex_wavetable_alloc(n);            break;
	case REAL_WORKSPACE:              o->space.rws  = gsl_fft_real_workspace_alloc(n);               break;
	case REAL_WAVETABLE:	          o->space.rwt  = gsl_fft_real_wavetable_alloc(n);               break;
	case HALFCOMPLEX_WAVETABLE:       o->space.hcwt = gsl_fft_halfcomplex_wavetable_alloc(n);        break;
	case COMPLEX_WORKSPACE_FLOAT:     o->space.cwsf  = gsl_fft_complex_workspace_float_alloc(n);     break;
	case COMPLEX_WAVETABLE_FLOAT:     o->space.cwtf  = gsl_fft_complex_wavetable_float_alloc(n);     break;
	case REAL_WORKSPACE_FLOAT:        o->space.rwsf  = gsl_fft_real_workspace_float_alloc(n);        break;
	case REAL_WAVETABLE_FLOAT:	  o->space.rwtf  = gsl_fft_real_wavetable_float_alloc(n);        break;
	case HALFCOMPLEX_WAVETABLE_FLOAT: o->space.hcwtf = gsl_fft_halfcomplex_wavetable_float_alloc(n); break;
	default: gsl_error("Got unknown switch", filename, __LINE__, GSL_ESANITY); return NULL; break;
	}
	return (PyObject *) o;
}



#define PyGSL_SPACE_ALLOC(TYPE)                               \
static PyObject *                                             \
PyGSL_fft_space_init_ ## TYPE (PyObject *self, PyObject *args)\
{                                                             \
     return PyGSL_fft_space_init(self, args, TYPE);           \
}                                                             
PyGSL_SPACE_ALLOC(COMPLEX_WORKSPACE)
PyGSL_SPACE_ALLOC(COMPLEX_WAVETABLE)
PyGSL_SPACE_ALLOC(REAL_WORKSPACE)      
PyGSL_SPACE_ALLOC(REAL_WAVETABLE)
PyGSL_SPACE_ALLOC(HALFCOMPLEX_WAVETABLE)

PyGSL_SPACE_ALLOC(COMPLEX_WORKSPACE_FLOAT)
PyGSL_SPACE_ALLOC(COMPLEX_WAVETABLE_FLOAT)
PyGSL_SPACE_ALLOC(REAL_WORKSPACE_FLOAT)      
PyGSL_SPACE_ALLOC(REAL_WAVETABLE_FLOAT)
PyGSL_SPACE_ALLOC(HALFCOMPLEX_WAVETABLE_FLOAT)


/*
typedef int (complex_transform)(gsl_complex_packed_array
          DATA, size_t STRIDE, size_t N, const
          gsl_fft_complex_wavetable * WAVETABLE,
          gsl_fft_complex_workspace * WORK);
*/
typedef int transform(void * data, size_t stride, size_t N, const void *, void *);
typedef int transform_r2(void * data, size_t stride, size_t N);


typedef void * pygsl_fft_helpn_t(int);
typedef void * pygsl_fft_help_t(void *);

struct _pygsl_fft_help_s {
	pygsl_fft_helpn_t  * space_alloc;
	pygsl_fft_help_t   * space_free;
	pygsl_fft_helpn_t  * table_alloc;
	pygsl_fft_help_t   * table_free;
	enum pygsl_fft_space_type space_type;
	enum pygsl_fft_space_type table_type;
	void * space;
	void * table;
	int free_space;
	int free_table;
};

typedef struct _pygsl_fft_help_s pygsl_fft_help_s;

static const  
pygsl_fft_help_s complex_helpers = {(pygsl_fft_helpn_t *) gsl_fft_complex_workspace_alloc, 
				    (pygsl_fft_help_t *)  gsl_fft_complex_workspace_free, 
				    (pygsl_fft_helpn_t *) gsl_fft_complex_wavetable_alloc, 
				    (pygsl_fft_help_t *)  gsl_fft_complex_wavetable_free,
                                    COMPLEX_WORKSPACE, COMPLEX_WAVETABLE};

static const  
pygsl_fft_help_s halfcomplex_helpers = {(pygsl_fft_helpn_t *) gsl_fft_real_workspace_alloc, 
					(pygsl_fft_help_t *)  gsl_fft_real_workspace_free, 
					(pygsl_fft_helpn_t *) gsl_fft_halfcomplex_wavetable_alloc, 
					(pygsl_fft_help_t *)  gsl_fft_halfcomplex_wavetable_free, 
					REAL_WORKSPACE, HALFCOMPLEX_WAVETABLE};
static const 
pygsl_fft_help_s real_helpers = {(pygsl_fft_helpn_t *) gsl_fft_real_workspace_alloc, 
				 (pygsl_fft_help_t *)  gsl_fft_real_workspace_free, 
				 (pygsl_fft_helpn_t *) gsl_fft_real_wavetable_alloc, 
				 (pygsl_fft_help_t *)  gsl_fft_real_wavetable_free, 
				 REAL_WORKSPACE, REAL_WAVETABLE};
static const 
pygsl_fft_help_s complex_helpers_float = {(pygsl_fft_helpn_t *) gsl_fft_complex_workspace_float_alloc, 
				    (pygsl_fft_help_t *)  gsl_fft_complex_workspace_float_free, 
				    (pygsl_fft_helpn_t *) gsl_fft_complex_wavetable_float_alloc, 
				    (pygsl_fft_help_t *)  gsl_fft_complex_wavetable_float_free,
                                    COMPLEX_WORKSPACE, COMPLEX_WAVETABLE};

static const 
pygsl_fft_help_s halfcomplex_helpers_float = {(pygsl_fft_helpn_t *) gsl_fft_real_workspace_float_alloc, 
					(pygsl_fft_help_t *)  gsl_fft_real_workspace_float_free, 
					(pygsl_fft_helpn_t *) gsl_fft_halfcomplex_wavetable_float_alloc, 
					(pygsl_fft_help_t *)  gsl_fft_halfcomplex_wavetable_float_free, 
					REAL_WORKSPACE, HALFCOMPLEX_WAVETABLE};
static const 
pygsl_fft_help_s real_helpers_float = {(pygsl_fft_helpn_t *) gsl_fft_real_workspace_float_alloc, 
				 (pygsl_fft_help_t *)  gsl_fft_real_workspace_float_free, 
				 (pygsl_fft_helpn_t *) gsl_fft_real_wavetable_float_alloc, 
				 (pygsl_fft_help_t *)  gsl_fft_real_wavetable_float_free, 
				 REAL_WORKSPACE, REAL_WAVETABLE};

static int 
PyGSL_fft_helpers_alloc(PyObject *s_o, PyObject *t_o, pygsl_fft_help_s * h, int n)
{
	h->free_space = 0;
	h->free_table = 0;
	h->table = NULL;
	h->space = NULL;

	if(s_o){
		if(PyGSL_fft_space_check(s_o) && ((PyGSL_fft_space * )s_o)->type == h->space_type){
			h->space = ((PyGSL_fft_space * )s_o) ->space.v;
		} else {
			PyGSL_add_traceback(module, filename, __FUNCTION__, __LINE__ - 4);
			GSL_ERROR("Need a pygsl  fft space of proper type!", GSL_EINVAL);
		}
	}

	if(t_o){
		if(PyGSL_fft_space_check(t_o) && ((PyGSL_fft_space * )t_o)->type == h->table_type){
			h->table = ((PyGSL_fft_space * )t_o) ->space.v;
		} else {
			PyGSL_add_traceback(module, filename, __FUNCTION__, __LINE__ - 4);
			GSL_ERROR("Need a pygsl fft wave table of proper type!", GSL_EINVAL);
		}
	}
	/* Check for the approbriate type and initialise it!*/
	if(h->space == NULL || h->table == NULL){
		/* Store if I need to free these arrays */
		h->free_space = (h->space == NULL) ? 1 : 0;
		h->free_table = (h->table == NULL) ? 1 : 0;
		if(!h->space) h->space = h->space_alloc(n);
		if(!h->table) h->table = h->table_alloc(n);
		if(!h->space || !h->table)  
			return GSL_ENOMEM;
	}
	return GSL_SUCCESS;

}

static void
PyGSL_fft_helpers_free(pygsl_fft_help_s * h)
{
	if(h->table && h->free_table){ 
		h->table_free(h->table); 
		h->table = NULL;
	}
	if(h->space && h->free_space){
		h->space_free(h->space);  
		h->space = NULL;
	}
}
/* 
 * Copies real data to complex in the special way that it will be passed to the
 * transform with an offset of one! 
 */
static int
PyGSL_copy_real_to_complex(PyArrayObject *dst, PyArrayObject *src, enum pygsl_fft_mode mode)
{
	int i, n, n_check, n_2;

	n = src->dimensions[0];
	n_check = dst->dimensions[0];
	
	for(i = 0; i < n; ++i){

		double *srcd=NULL, *dstd=NULL;			
		float  *srcf=NULL, *dstf=NULL;			
		if(mode == MODE_DOUBLE){
			srcd = (double *)(src->data + src->strides[0] *  (i));
			n_2 = (i+1)/2;
			dstd = (double *)(dst->data + dst->strides[0] *  (n_2));
			if(n_2 >= n_check)
				GSL_ERROR("Complex array too small!", GSL_ESANITY);
			dstd[(i+1)%2] = *srcd;
			DEBUG_MESS(5, "R -> C [%d] srcd %e\t dstd %e + %ej", i, *srcd, dstd[0], dstd[1]);
		}else if(mode == MODE_FLOAT){
			srcf = (float *)(src->data + src->strides[0] *  (i));
			n_2 = (i+1)/2;
			dstf = (float *)(dst->data + dst->strides[0] *  (n_2));
			if(n_2 >= n_check)
				GSL_ERROR("Complex array too small!", GSL_ESANITY);
			dstf[(i+1)%2] = *srcd;			
		}
	}
	/* XXX Sometimes the last value must be set to zero ... */
	return GSL_SUCCESS;
	
}

/* Assumes special halfcomplex arrangement to be made and used ! */
static int
PyGSL_copy_halfcomplex_to_real(PyArrayObject *dst, PyArrayObject *src, double eps, enum pygsl_fft_mode mode
	 )
{
	int n, n_check, i, n_2;
	double *srcd=NULL, *dstd=NULL;
	float *srcf=NULL, *dstf=NULL;

	n_check = src->dimensions[0];
	n = dst->dimensions[0];

	/* The first element is a bit special */
	if(mode == MODE_DOUBLE){
		srcd = (double *)(src->data);	
		dstd = (double *)(dst->data);
	} else {
		srcf = (float *)(src->data);	
		dstf = (float *)(dst->data);
	}
	/* Should be zero ... */
	if(gsl_fcmp(PyGSL_FFT_MODE_SWITCH(mode, srcd[1], srcf[1]), 0,  eps) != 0)
		GSL_ERROR("The complex part of the nyquist freqency was not" 
			  "zero as it ought to be!", GSL_EINVAL);
	*dstd = *srcd;

	for(i = 1; i < n; ++i){
		n_2 = (i+1)/2;
		if(n_2 >= n_check){
			GSL_ERROR("Sizes of the complex array too small!", GSL_ESANITY);
		}
		if(mode == MODE_DOUBLE){
			srcd = (double *)(src->data + src->strides[0] * n_2);
			dstd = (double *)(dst->data + dst->strides[0] * i);
			*dstd = srcd[(i+1)%2];
			DEBUG_MESS(5, "C -> R [%d] srcd %e + %ej\t dstd %e", i, srcd[0], srcd[1], *dstd);
		} else {
			srcf = (float *)(src->data + src->strides[0] * n_2);
			dstf = (float *)(dst->data + dst->strides[0] * i);
			*dstf = srcf[(i+1)%2];
			DEBUG_MESS(5, "C -> R [%d] srcf %e + %ej\t dstf %e", i, srcf[0], srcf[1], *dstf);
		}
	}
	return GSL_SUCCESS;
}

static int
PyGSL_copy_complex_to_complex(PyArrayObject *dst, PyArrayObject *src,  enum pygsl_fft_mode mode)
{
	int n, n_check, i;

	FUNC_MESS_BEGIN();
	n = dst->dimensions[0];
	n_check = src->dimensions[0];
	if(n_check != n){
		GSL_ERROR("Sizes of the arrays did not match!", GSL_ESANITY);
	}
	for(i = 0; i < n; i ++){
		double *srcd=NULL, *dstd=NULL;
		float  *srcf=NULL, *dstf=NULL;
		if(mode == MODE_DOUBLE){
			srcd = (double *)(src->data + src->strides[0] * i);
			dstd = (double *)(dst->data + dst->strides[0] * i);
			dstd[0] = srcd[0];
			dstd[1] = srcd[1];
		} else {
			srcf = (float *)(src->data + src->strides[0] * i);
			dstf = (float *)(dst->data + dst->strides[0] * i);
			dstf[0] = srcf[0];
			dstf[1] = srcf[1];
		}
	}
	FUNC_MESS_END();
	return GSL_SUCCESS;
}

#if 0
/*
 * Copy a complex array to a real one or to the other ...
 */
static int
PyGSL_copy_complex_real(PyArrayObject *dst, PyArrayObject *src)
{
	int in_type, out_type;
	int flag = GSL_FAILURE, line = -1;


	FUNC_MESS_BEGIN();
	in_type  = src->descr->type_num;
	out_type = dst->descr->type_num;

	if(in_type ==  PyArray_CDOUBLE){
		DEBUG_MESS(2, "Src is a complex array!", NULL);		
	} else if (in_type ==  PyArray_DOUBLE){
		DEBUG_MESS(2, "Src is a real array!", NULL);
	}
	if(out_type ==  PyArray_CDOUBLE){
		DEBUG_MESS(2, "Dst is a complex array!", NULL);
	} else if (out_type ==  PyArray_DOUBLE){
		DEBUG_MESS(2, "Dst is a real array!", NULL);
	}

	if(out_type == PyArray_CDOUBLE && in_type == PyArray_CDOUBLE){
		if(PyGSL_copy_complex_to_complex(dst, src) != GSL_SUCCESS){
			line = __LINE__ - 1;
			goto fail;			
		}
	} else 	if(out_type == PyArray_DOUBLE && in_type == PyArray_CDOUBLE){
		if(PyGSL_copy_halfcomplex_to_real(dst, src) != GSL_SUCCESS){
			line = __LINE__ - 1;
			goto fail;
		}
	} else if(out_type == PyArray_CDOUBLE && in_type == PyArray_DOUBLE){
		if(PyGSL_copy_real_to_complex(dst, src) != GSL_SUCCESS){
			line = __LINE__ - 1;
			goto fail;
		}
	} else{
		flag = GSL_ESANITY;
		line = __LINE__;
		goto fail;
	}
	FUNC_MESS_END();
	return GSL_SUCCESS;
  fail:
	FUNC_MESS("Fail");
	gsl_error("Not specifed error", filename, line, flag);
	PyGSL_add_traceback(module, filename, __FUNCTION__, line);
	return flag;
}
#endif 

/*
 * Only shift the last one. Assumes that it was passed to the GSL function with
 * an offset of one. Further assumes an contingous array.
 */
static int
PyGSL_fft_halfcomplex_unpack(PyArrayObject *a, int n_orig,  enum pygsl_fft_mode mode)
{
	double *d;
	float *f;
	FUNC_MESS_BEGIN();
	if(mode == MODE_DOUBLE){
		d = (double *) a->data;
		d[0] = d[1];
		d[1] = 0.0;
		/* Set the last imaginary to zero for even length as it ought to be */
		if(n_orig%2)
			d[n_orig] = 0.0; 
	}else{
		f = (float *) a->data;
		f[0] = f[1];
		f[1] = 0.0;
		/* Set the last imaginary to zero for even length as it ought to be */
		if(n_orig%2)
			f[n_orig] = 0.0; 

	}
	FUNC_MESS_END();
	return GSL_SUCCESS;
}

/*
 * I only need to reorder the imaginary data?
 * I have to do it inplace thus I can not use the gsl function ...
 */
static PyObject *
PyGSL_fft_halfcomplex_radix2_unpack(PyObject *self, PyObject *args)
{

	PyObject *a_o=NULL;
	PyArrayObject *a=NULL, *r=NULL;
	int i, n, rn;
        double *data, *real, *imag;

	FUNC_MESS_BEGIN();
	if(!PyArg_ParseTuple(args, "O",&a_o))
		return NULL;

	a = PyGSL_PyArray_PREPARE_gsl_vector_view(a_o, PyArray_DOUBLE, 0, -1, 1, NULL);
	if(a == NULL)
		goto fail;
	n = a->dimensions[0];
	if(n%2 != 0){
		gsl_error("The length of the vector must be a multiple of two!",
			  __FILE__, __LINE__, GSL_EDOM);		goto fail;
	}
	rn = n / 2 + 1;
	if((r = (PyArrayObject *) PyGSL_New_Array(1, &rn, PyArray_CDOUBLE)) == NULL)
		goto fail;
	assert(r->dimensions[0] == rn);
	/* first one special */
	data = (double *) r->data;
	data[0] = a->data[0];
	data[1] = 0.0;

	for(i = 1; i < rn - 1; ++i){
		data    = (double *)(r->data + r->strides[0] * i);
		real    = (double *)(a->data + a->strides[0] * i);
		imag    = (double *)(a->data + a->strides[0] * (n-i));
		assert(i>0 && i < n);
		data[0] = *real;
		data[1] = *imag;
		DEBUG_MESS(6, "n = %d, i = %d, n - i = %d, rn = %d", n, i, n - i, rn);
		DEBUG_MESS(6, "real = %e, %p, imag = %e, %p", *real, real, *imag, imag);
		DEBUG_MESS(5, "Data[%d] = %e + %e j", i, data[0], data[1]);
	}
	data    =   (double *)(r->data + r->strides[0] * (rn-1));
	data[0] = *((double *)(a->data + a->strides[0] * (n/2)));
	data[1] = 0.0;

	/* data[n_orig] = 0.0; */
	Py_DECREF(a);
        FUNC_MESS_END();
	return (PyObject *) r;
  fail:
	Py_XDECREF(a);
	Py_XDECREF(r);
	return NULL;
}
static PyObject *
PyGSL_fft_halfcomplex_radix2_unpack_float(PyObject *self, PyObject *args)
{

	PyObject *a_o=NULL;
	PyArrayObject *a=NULL, *r=NULL;
	int i, n, rn;
        float *data, *real, *imag;

	FUNC_MESS_BEGIN();
	if(!PyArg_ParseTuple(args, "O",&a_o))
		return NULL;

	a = PyGSL_PyArray_PREPARE_gsl_vector_view(a_o, PyArray_FLOAT, 0, -1, 1, NULL);
	if(a == NULL)
		goto fail;
	n = a->dimensions[0];
	if(n%2 != 0){
		gsl_error("The length of the vector must be a multiple of two!",
			  __FILE__, __LINE__, GSL_EDOM);		goto fail;
	}
	rn = n / 2 + 1;
	if((r = (PyArrayObject *) PyGSL_New_Array(1, &rn, PyArray_CFLOAT)) == NULL)
		goto fail;
	assert(r->dimensions[0] == rn);
	/* first one special */
	data = (float *) r->data;
	data[0] = a->data[0];
	data[1] = 0.0;

	for(i = 1; i < rn - 1; ++i){
		data    = (float *)(r->data + r->strides[0] * i);
		real    = (float *)(a->data + a->strides[0] * i);
		imag    = (float *)(a->data + a->strides[0] * (n-i));
		assert(i>0 && i < n);
		data[0] = *real;
		data[1] = *imag;
		DEBUG_MESS(6, "n = %d, i = %d, n - i = %d, rn = %d", n, i, n - i, rn);
		DEBUG_MESS(6, "real = %e, %p, imag = %e, %p", *real, real, *imag, imag);
		DEBUG_MESS(5, "Data[%d] = %e + %e j", i, data[0], data[1]);
	}
	data    =   (float *)(r->data + r->strides[0] * (rn-1));
	data[0] = *((float *)(a->data + a->strides[0] * (n/2)));
	data[1] = 0.0;

	/* data[n_orig] = 0.0; */
	Py_DECREF(a);
        FUNC_MESS_END();
	return (PyObject *) r;
  fail:
	Py_XDECREF(a);
	Py_XDECREF(r);
	return NULL;
}

# if 0
        /*
         * All the arithmetic here will be only possible if the array is
         * continguous.
         */
        if(a->strides[0] == sizeof(double) *2)
                ;
        else
                GSL_ERROR("Can only unpack continuous halfcomplex arrays!", GSL_ESANITY);

        n = a->dimensions[0] - 1;

	if(n * 2 < n_orig)
		GSL_ERROR("Original size too big!!", GSL_ESANITY);
	if(n_orig %2 == 0)
		;
	else
		GSL_ERROR("Got non even length for radix2!?!", GSL_ESANITY);

        DEBUG_MESS(2, "Unpacking a half complex array of size %d, storage size = %d", 
                   n_orig, a->dimensions[0]);


	data = (double *) a->data;
	data[0] = data[1];
	data[1] = 0.0;

	/* Take the shift into account 	++data; */

	/*
	 * now data starts were the real array would start withot the shift
	 * trick
	 */
	for(i = 1; i < n_orig+1; i++)
		DEBUG_MESS(5, "Putting data[%d]= %e", i, data[i]);

	/* For two destinct arrays ....
	for(i=1; i< n; ++i){
		newdata[i*2] = data[i+1];
		newdata[i*2+1] = data[n_orig-i+1];
	}
	*/

	for(i = n_orig/2 - 1; i > 0; --i){
		/* move the real data backward */
		tmp1 = data[i+1];
		tmp2 = data[n_orig-i+1];
		DEBUG_MESS(5, "Putting %e + %ej from %d,%d -> %d %d", tmp1,
			   tmp2, i+1, n_orig-i+1, i*2, i*2+1);

		/* get the imaginary data from the end */
		if(i >= n)
			GSL_ERROR("Out of range for unpack!", GSL_ESANITY);
		tmp3 = data[i*2];
		tmp4 = data[i*2+1];
		data[i*2] = tmp1;
		data[i*2+1] = tmp2;		
	}
#endif 


/*
 * A catch all of the various type handling routines. Perhaps too much in one function!
 */
static PyArrayObject *
PyGSL_Shadow_array(PyObject *shadow, PyObject *master,  enum pygsl_fft_mode mode)
{
	PyArrayObject * ret = NULL, *s=NULL, *m=NULL;
	int line = -1;
	
	/* Check if I got a return array */
	if(!PyArray_Check(master)){
		line = __LINE__ - 1;
		goto fail;
	}
	m = (PyArrayObject *) master;
	if(shadow == NULL){
		FUNC_MESS("Generating an output array");
		ret =  (PyArrayObject *) PyGSL_Copy_Array(m);
		if(ret == NULL){
			line = __LINE__ -2;
			goto fail;
		}
	} else {		
		if (shadow ==  master) {
			Py_INCREF(shadow);
			ret = m;
		}else{	
			FUNC_MESS("Copying input to output array");
			/* Check if it is an array of the approbriate size */
			s = (PyArrayObject *) shadow;
			if((PyArray_Check(s)) && (s->nd == 1 ) 
			   && (s->descr->type_num == m->descr->type_num) 
			   && (s->dimensions[0] == m->dimensions[0])){
				Py_INCREF(s);
				ret = (PyArrayObject *) s;
			} else {
				gsl_error("The return array must be of approbriate size and type!", 
					  filename, __LINE__, GSL_EINVAL);
				line = __LINE__ -7;
				goto fail;
			}
			if(PyGSL_ERROR_FLAG(PyGSL_copy_complex_to_complex(s, m, mode) != GSL_SUCCESS)){
				line = __LINE__ -1;
				goto fail;			
			}
		}
	}
	return ret;
  fail:
	PyGSL_add_traceback(module, filename, __FUNCTION__, line);
	return NULL;
}

static int
PyGSL_guess_halfcomplex_length(PyArrayObject *a, int length, double eps,  enum pygsl_fft_mode mode)
{
	int n, call_n = -1;
	void *v;

	n = a->dimensions[0];
	if(length == -1){
		/* length was not given, try to guess */
		v = (a->data + a->strides[0] * (n - 1));
		if(gsl_fcmp(PyGSL_FFT_MODE_SWITCH(mode, ((double *)v)[1], ((float *)v)[1]), 0,  eps) == 0){
			call_n = n*2-2;
		}else{
			/* 
			 * The last element was close to zero, thus I assume
			 *  that I got  original data of even length.
			 */
			call_n = n*2-1;
		}			
	}else if(length < -1){
		gsl_error("The given length must be a positive number!",
			  __FILE__, __LINE__, GSL_EINVAL);
		return length;
	}else{
		call_n = length;
	}
	DEBUG_MESS(5, "Using a length of %d", call_n);
	return call_n;

}

static PyObject *
PyGSL_fft_halfcomplex(PyObject *self, PyObject *args, transform * transform,  enum pygsl_fft_mode mode)
{
	PyObject *data = NULL, *s_o= NULL, *t_o = NULL;
	PyArrayObject *a = NULL, *r=NULL;
	
	int strides=0;
	int flag, call_n, return_n, length=-1;
	int line = -1;
	double eps=1e-6;

	FUNC_MESS_BEGIN();

	if(! PyArg_ParseTuple(args, "O|iOOd",&data, &length, &s_o, &t_o, &eps)){
		return NULL;
	}
	
	a = PyGSL_PyArray_PREPARE_gsl_vector_view(data, PyGSL_FFT_MODE_SWITCH(mode, PyArray_CDOUBLE, PyArray_CFLOAT), 0, -1, 1, NULL);
	if(a == NULL)
		return NULL;
	call_n = PyGSL_guess_halfcomplex_length(a, length, eps, mode);
	if(call_n < 0)
		goto fail;
	return_n = call_n;

	PyGSL_fft_helpers_alloc(s_o, t_o,  PyGSL_FFT_MODE_SWITCH(mode,  halfcomplex_helpers, halfcomplex_helpers_float));
	

	r = (PyArrayObject *) PyGSL_New_Array(1, &return_n, PyArray_DOUBLE);			
	if(r == NULL){
		line = __LINE__ - 2;
		goto fail;
	}
	if(PyGSL_ERROR_FLAG(PyGSL_copy_halfcomplex_to_real(r, a, eps, mode) != GSL_SUCCESS)){
		line = __LINE__ - 1;
		goto fail;			
	}

	flag = PyGSL_STRIDE_RECALC(r->strides[0], sizeof(double), &strides);
	if(flag != GSL_SUCCESS){
		line = __LINE__ - 2;
		goto fail;
	}

	flag = transform((double *)(r->data), strides, call_n, table, space);
	if(PyGSL_ERROR_FLAG(flag) != GSL_SUCCESS){
		line = __LINE__ - 2;
		goto fail;
	}
	PyGSL_fft_helpers_free(PyGSL_FFT_MODE_SWITCH(mode,  halfcomplex_helpers, halfcomplex_helpers_float));
	Py_DECREF(a);
	FUNC_MESS_END();
	return (PyObject *) r;

  fail:
	FUNC_MESS("Fail");
	PyGSL_add_traceback(module, filename, __FUNCTION__, line);
	PyGSL_fft_helpers_free(PyGSL_FFT_MODE_SWITCH(mode,  halfcomplex_helpers, halfcomplex_helpers_float));
	Py_XDECREF(a);
	Py_XDECREF(r);
	return NULL;
}

static PyObject *
PyGSL_fft_halfcomplex_radix2(PyObject *self, PyObject *args, transform_r2 * transform,  enum pygsl_fft_mode mode)
{
	PyObject *data = NULL;
	PyArrayObject *a = NULL, *r=NULL;
	
	int strides=0;
	int flag, call_n, return_n;
	int line = -1;

	FUNC_MESS_BEGIN();

	if(! PyArg_ParseTuple(args, "O", &data)){
		return NULL;
	}
	
	a = PyGSL_PyArray_PREPARE_gsl_vector_view(data, PyArray_CDOUBLE, 0, -1, 1, NULL);
	if(a == NULL)
		return NULL;
	call_n = a->dimensions[0];
	return_n = call_n;

	r = (PyArrayObject *) PyGSL_Copy_Array(a);
	if(r == NULL){
		line = __LINE__ - 2;
		goto fail;
	}
	flag = PyGSL_STRIDE_RECALC(r->strides[0], sizeof(double), &strides);
	if(flag != GSL_SUCCESS){
		line = __LINE__ - 2;
		goto fail;
	}

	flag = transform((double *)(r->data), strides, call_n);
	if(PyGSL_ERROR_FLAG(flag) != GSL_SUCCESS){
		line = __LINE__ - 2;
		goto fail;
	}
	Py_DECREF(a);
	FUNC_MESS_END();
	return (PyObject *) r;

  fail:
	FUNC_MESS("Fail");
	PyGSL_add_traceback(module, filename, __FUNCTION__, line);
	Py_XDECREF(a);
	Py_XDECREF(r);
	return NULL;
}

static PyObject *
PyGSL_fft_real(PyObject *self, PyObject *args, transform * transform,  enum pygsl_fft_mode mode)
{
	PyObject *data = NULL, *s_o= NULL, *t_o = NULL;
	PyArrayObject *a = NULL, *r=NULL;
	
	gsl_fft_real_workspace  *space=NULL;
	gsl_fft_real_wavetable  *table=NULL;
	int strides=0, n=0, line=-1;
	int free_space = 0, free_table=0, flag, call_n, return_n;


	FUNC_MESS_BEGIN();

	if(! PyArg_ParseTuple(args, "O|OO", &data, &s_o, &t_o)){
		return NULL;
	}
	
	a = PyGSL_PyArray_PREPARE_gsl_vector_view(data, PyArray_DOUBLE, 0, -1, 1, NULL);
	if(a == NULL)
		return NULL;
	n = a->dimensions[0];
	call_n = n;
	return_n = n/2 + 1;

	if(s_o){
		flag = PyGSL_real_fft_work_space_check(s_o);
		if(flag){
			space = ((PyGSL_fft_space * )s_o) ->space.rws;
		} else {
			line = __LINE__ -5;
			gsl_error("Need a pygsl fft space!", filename, __LINE__ - 5, GSL_EINVAL);
			goto fail;
		}
	}

	if(t_o){
		flag = PyGSL_real_fft_wave_table_check(t_o);
		if(flag){
			table = ((PyGSL_fft_space * )t_o) ->space.rwt;
		} else {
			line = __LINE__ -5;
			gsl_error("Need a pygsl fft table!", filename, __LINE__ - 5, GSL_EINVAL);
			goto fail;
		}
	}

	/* Check for the approbriate type and initialise it!*/
	if(space == NULL || table == NULL){
		/* Store if I need to free these arrays */
		free_space = (space == NULL) ? 1 : 0;
		free_table = (table == NULL) ? 1 : 0;
		if(!space) space = gsl_fft_real_workspace_alloc(call_n);
		if(!table) table = gsl_fft_real_wavetable_alloc(call_n);
		if(!space || !table)
			goto fail;

	}
	
	/* Check if I got a return array */
	r = (PyArrayObject *) PyGSL_New_Array(1, &return_n, PyArray_CDOUBLE);			
	if(r == NULL){
		line = __LINE__ -2;
		goto fail;
	}
	if(PyGSL_copy_real_to_complex(r, a, MODE_DOUBLE) != GSL_SUCCESS){
		line = __LINE__ -1;
		goto fail;			
	}
	flag = PyGSL_STRIDE_RECALC(r->strides[0], sizeof(double) * 2, &strides);
	if(flag != GSL_SUCCESS){
		line = __LINE__ -2;
		goto fail;
	}

	FUNC_MESS("Transforming ...");
	flag = transform(((double *) r->data)+1, strides, call_n, table, space);
	FUNC_MESS(" ... Done");
	if(PyGSL_ERROR_FLAG(flag) != GSL_SUCCESS){
		line = __LINE__ -2;
		goto fail;
	}
	
         /* Rearange half complex data */
	if(PyGSL_fft_halfcomplex_unpack(r, call_n, mode) != GSL_SUCCESS){
		line = __LINE__ -1;
		goto fail;
	}

	if(free_space == 1 && space != NULL) gsl_fft_real_workspace_free(space);
	if(free_table == 1 && table != NULL) gsl_fft_real_wavetable_free(table);
	Py_DECREF(a);
	FUNC_MESS_END();
	return (PyObject *) r;

  fail:
	FUNC_MESS("Fail");
	PyGSL_add_traceback(module, filename, __FUNCTION__, line);
	if(free_space == 1 && space != NULL) gsl_fft_real_workspace_free(space);
	if(free_table == 1 && table != NULL) gsl_fft_real_wavetable_free(table);
	Py_XDECREF(a);
	Py_XDECREF(r);
	return NULL;
}

static PyObject *
PyGSL_fft_real_radix2(PyObject *self, PyObject *args, transform_r2 * transform,  enum pygsl_fft_mode mode)
{
	PyObject *data = NULL;
	PyArrayObject *a = NULL, *r=NULL;
	
	int strides=0, n=0, line=-1;
	int  flag, call_n, return_n;


	FUNC_MESS_BEGIN();

	if(! PyArg_ParseTuple(args, "O", &data)){
		return NULL;
	}
	
	a = PyGSL_PyArray_PREPARE_gsl_vector_view(data, PyArray_DOUBLE, 0, -1, 1, NULL);
	if(a == NULL)
		return NULL;
	n = a->dimensions[0];
	call_n = n;
	return_n = n;

	
	
	/* Check if I got a return array */
	r = (PyArrayObject *) PyGSL_Copy_Array(a);
	if(r == NULL)
		goto fail;

	flag = PyGSL_STRIDE_RECALC(r->strides[0], sizeof(double), &strides);
	if(flag != GSL_SUCCESS){
		line = __LINE__ -2;
		goto fail;
	}
	flag = transform(((double *)r->data), strides, call_n);
	if(PyGSL_ERROR_FLAG(flag) != GSL_SUCCESS){
		line = __LINE__ -2;
		goto fail;
	}
	/* No rearange handled in a separate function ... */
	Py_DECREF(a);
	FUNC_MESS_END();
	return (PyObject *) r;

  fail:
	FUNC_MESS("Fail");
	PyGSL_add_traceback(module, filename, __FUNCTION__, line);
	Py_XDECREF(a);
	Py_XDECREF(r);
	return NULL;
}

static PyObject *
PyGSL_complex_fft_(PyObject *self, PyObject *args, transform * transform,  enum pygsl_fft_mode mode)
{
	PyObject *data = NULL, *s_o= NULL, *t_o = NULL, *ret=NULL;
	PyArrayObject *a = NULL, *r=NULL;
	
	gsl_fft_complex_workspace  *space=NULL;
	gsl_fft_complex_wavetable  *table=NULL;
	int strides=0, n=0;
	int free_space = 0, free_table=0, flag, call_n;


	FUNC_MESS_BEGIN();
	if(!PyArg_ParseTuple(args, "O|OOO", &data, &s_o, &t_o, &ret)){
		return NULL;
	}
	
	a = PyGSL_PyArray_PREPARE_gsl_vector_view(data, PyArray_CDOUBLE, 0, -1, 1, NULL);
	if(a == NULL)
		goto fail;

	n = a->dimensions[0];
	call_n = n;

	r = PyGSL_Shadow_array((PyObject *) ret, (PyObject *) a, mode);
	if(r == NULL)
		goto fail;
	/* 
	 *  Return n is used to allocate an array, while call_n is the length passed on.
	 *  This is necessary as the halfcomplex transform needs space to store the nyquist 
	 *  frequency.
	 *
	 *  The following assert is protecting against surprises of missing space.
	 */
	/*
	if(call_n > return_n){
		fprintf(stderr, "In %s at Line %d call_n = %d, return_n = %d",
			filename, __LINE__, call_n, return_n);
		gsl_error("call_n larger than return_n!", filename, __LINE__ - 2, GSL_ESANITY); goto fail;
	}
	*/
	if(s_o){		
		flag = PyGSL_complex_fft_work_space_check(s_o);
		if(flag){
			space = ((PyGSL_fft_space *) s_o)->space.cws;
		} else {
			gsl_error("Need a pygsl complex fft space!", filename, __LINE__, GSL_EINVAL);
			PyGSL_add_traceback(module, filename, __FUNCTION__, __LINE__ - 5);
			goto fail;
		}
	}
	
	if(t_o){
		flag = PyGSL_complex_fft_wave_table_check(t_o);
		if(flag){
			table = ((PyGSL_fft_space *) t_o) ->space.cwt;
		} else {
			gsl_error("Need a pygsl complex fft wave table!", filename, __LINE__, GSL_EINVAL);
			PyGSL_add_traceback(module, filename, __FUNCTION__, __LINE__ - 5);
			goto fail;
		}
	}
	
        /*
	 * Check, if I have to init the the tables
	 */
	if(space == NULL || table == NULL){
		/* Store if I need to free these arrays */
		free_space = (space == NULL) ? 1 : 0;
		free_table = (table == NULL) ? 1 : 0;
		if(!space) space = gsl_fft_complex_workspace_alloc(call_n);
		if(!table) table = gsl_fft_complex_wavetable_alloc(call_n);
		if(!space || !table)
			goto fail;
	}
	

	flag = PyGSL_STRIDE_RECALC(r->strides[0], sizeof(double) * 2, &strides);
	if(flag != GSL_SUCCESS){
		goto fail;
	}

	DEBUG_MESS(2, "Array is at %p data at %p strides = %d length = %d", (void *) r, (void *) r->data, 
		   r->strides[0], r->dimensions[0]);
	DEBUG_MESS(2, "Starting a transform with an array of a size of %d and a stride of %d", call_n, strides);

	flag = transform((double *) r->data, strides, call_n, table, space);
	if(PyGSL_ERROR_FLAG(flag) != GSL_SUCCESS){
		goto fail;
	}
	if(free_space == 1 && space != NULL) gsl_fft_complex_workspace_free(space);
	if(free_table == 1 && table != NULL) gsl_fft_complex_wavetable_free(table);
	Py_DECREF(a);
	FUNC_MESS_END();
	return (PyObject *) r;

  fail:
	FUNC_MESS("Fail");
	Py_XDECREF(a);
	Py_XDECREF(r);
	if(free_space == 1 && space != NULL) gsl_fft_complex_workspace_free(space);
	if(free_table == 1 && table != NULL) gsl_fft_complex_wavetable_free(table);
	return NULL;
}

static PyObject *
PyGSL_complex_fft_radix2(PyObject *self, PyObject *args, transform_r2 * transform,  enum pygsl_fft_mode mode)
{
	PyObject *data = NULL, *ret=NULL;
	PyArrayObject *a = NULL, *r=NULL;
	
	int strides=0, n=0, flag;


	FUNC_MESS_BEGIN();
	if(!PyArg_ParseTuple(args, "O|O", &data,  &ret)){
		return NULL;
	}
	
	a = PyGSL_PyArray_PREPARE_gsl_vector_view(data, PyArray_CDOUBLE, 0, -1, 1, NULL);
	if(a == NULL)
		goto fail;
	n = a->dimensions[0];
	r = PyGSL_Shadow_array((PyObject *) ret, (PyObject *) a, mode);
	if(r == NULL)
		goto fail;
	flag = PyGSL_STRIDE_RECALC(r->strides[0], sizeof(double) * 2, &strides);
	if(flag != GSL_SUCCESS){
		goto fail;
	}

	DEBUG_MESS(2, "Array is at %p data at %p strides = %d length = %d", (void *) r, (void *) r->data, 
		   r->strides[0], r->dimensions[0]);
	DEBUG_MESS(2, "Starting a transform with an array of a size of %d and a stride of %d", n, strides);
	flag = transform((double *) r->data, strides, n);
	if(PyGSL_ERROR_FLAG(flag) != GSL_SUCCESS){
		goto fail;
	}
	Py_DECREF(a);
	FUNC_MESS_END();
	return (PyObject *) r;

  fail:
	FUNC_MESS("Fail");
	Py_XDECREF(a);
	Py_XDECREF(r);
	return NULL;
}

/*
 int gsl_fft_real_transform (double DATA[], size_t STRIDE,
          size_t N, const gsl_fft_real_wavetable * WAVETABLE,
          gsl_fft_real_workspace * WORK)
 int gsl_fft_halfcomplex_transform (double DATA[], size_t
          STRIDE, size_t N, const gsl_fft_halfcomplex_wavetable *
          WAVETABLE, gsl_fft_real_workspace * WORK)
*/

#define PyGSL_COMPLEX(direction) \
        static PyObject * \
	PyGSL_complex_fft_ ## direction(PyObject *self, PyObject *args){\
        PyObject *r;\
        FUNC_MESS_BEGIN();\
	r = PyGSL_complex_fft_(self, args, (transform * )gsl_fft_complex_ ## direction, MODE_DOUBLE); \
        FUNC_MESS_END();\
	return r;\
        }

PyGSL_COMPLEX(forward)
PyGSL_COMPLEX(backward)
PyGSL_COMPLEX(inverse)

#define PyGSL_COMPLEX_RADIX2(direction) \
        static PyObject * \
	PyGSL_complex_fft_radix2_ ## direction(PyObject *self, PyObject *args){\
        PyObject *r;\
        FUNC_MESS_BEGIN();\
	r = PyGSL_complex_fft_radix2(self, args, (transform_r2 * )gsl_fft_complex_radix2_ ## direction, MODE_DOUBLE); \
        FUNC_MESS_END();\
	return r;\
        }

PyGSL_COMPLEX_RADIX2(forward)
PyGSL_COMPLEX_RADIX2(backward)
PyGSL_COMPLEX_RADIX2(inverse)

PyGSL_COMPLEX_RADIX2(dif_forward)
PyGSL_COMPLEX_RADIX2(dif_backward)
PyGSL_COMPLEX_RADIX2(dif_inverse)

#define PyGSL_REAL_RADIX2(direction) \
        static PyObject * \
	PyGSL_real_fft_radix2_ ## direction(PyObject *self, PyObject *args){\
        PyObject *r;\
        FUNC_MESS_BEGIN();\
	r = PyGSL_fft_real_radix2(self, args, (transform_r2 * )gsl_fft_real_radix2_ ## direction, MODE_DOUBLE); \
        FUNC_MESS_END();\
	return r;\
        }

PyGSL_REAL_RADIX2(transform)

#define PyGSL_REAL(direction) \
        static PyObject * \
	PyGSL_real_fft_ ## direction(PyObject *self, PyObject *args){\
        PyObject *r;\
        FUNC_MESS_BEGIN();\
	r = PyGSL_fft_real(self, args, (transform * )gsl_fft_real_ ## direction, MODE_DOUBLE); \
        FUNC_MESS_END();\
	return r;\
        }

PyGSL_REAL(transform)

#define PyGSL_HALFCOMPLEX(direction) \
        static PyObject * \
	PyGSL_halfcomplex_fft_ ## direction(PyObject *self, PyObject *args){\
	return PyGSL_fft_halfcomplex(self, args, (transform * )gsl_fft_halfcomplex_ ## direction, MODE_DOUBLE); \
        }

PyGSL_HALFCOMPLEX(transform)
PyGSL_HALFCOMPLEX(inverse)

#define PyGSL_HALFCOMPLEX_RADIX2(direction) \
        static PyObject * \
	PyGSL_halfcomplex_fft_radix2_ ## direction(PyObject *self, PyObject *args){\
	return PyGSL_fft_halfcomplex_radix2(self, args, (transform_r2 * )gsl_fft_halfcomplex_radix2_ ## direction, MODE_DOUBLE); \
        }

PyGSL_HALFCOMPLEX_RADIX2(transform)
PyGSL_HALFCOMPLEX_RADIX2(inverse)

static const char fft_module_doc[] = "\
Wrapper for the FFT Module of the GSL Library\n\
\n\
";
static const char cws_doc[] = "\
Complex Workspace\n\
\n\
Needed as working space for mixed radix routines.\n\
\n\
Input:\n\
    n ... Length of the data to transform\n\
";
static const char cwt_doc[] = "\
Complex Wavetable\n\
\n\
   Stores the precomputed trigonometric functions\n\
Input:\n\
    n ... Length of the data to transform\n\
";
static const char rws_doc[] = "\
Real Workspace\n\
\n\
Needed as working space for mixed radix routines.\n\
\n\
Input:\n\
    n ... Length of the data to transform\n\
";
static const char rwt_doc[] = "\
Real Wavetable\n\
\n\
   Stores the precomputed trigonometric functions\n\
Input:\n\
    n ... Length of the data to transform\n\
";

static const char hcwt_doc[] = "\
Half Complex Wavetable\n\
\n\
   Stores the precomputed trigonometric functions\n\
Input:\n\
    n ... Length of the data to transform\n\
";
#define TRANSFORM_INPUT "\
Input:\n\
      data ... an array of complex numbers\n\
\n\
Optional Input:\n\
      If these objects are not provided, they will be generated by the\n\
      function automatically.\n\
\n\
      space  ... a workspace of approbriate type and size\n\
      table  ... a wavetable of approbriate type and size\n\
      output ... array to store the output into. GSL computes the FFT\n\
                 in place. So if this array is provided, the wrapper\n\
                 will use this array as output array. If the input and\n\
                 output array are identical no internal copy will be\n\
                 made. \n\
                 This works only for the complex transform types!\n"

#define TRANSFORM_INPUT_RADIX2 "\
Input:\n\
      data ... an array of complex numbers\n\
\n\
Optional Input:\n\
      If these objects are not provided, they will be generated by the\n\
      function automatically.\n\
\n\
      output ... array to store the output into. GSL computes the FFT\n\
                 in place. So if this array is provided, the wrapper\n\
                 will use this array as output array. If the input and\n\
                 output array are identical no internal copy will be\n\
                 made. \n\
                 This works only for the complex transform types!\n"

#define TRANSFORM_INPUT_REAL "\
Input:\n\
      data ... an array of real numbers\n\
\n\
Optional Input:\n\
      If these objects are not provided, they will be generated by the\n\
      function automatically.\n\
\n\
      space  ... a workspace of approbriate type and size\n\
      table  ... a wavetable of approbriate type and size\n\
      output ... array to store the output into. GSL computes the FFT\n\
                 in place. So if this array is provided, the wrapper\n\
                 will use this array as output array. If the input and\n\
                 output array are identical no internal copy will be\n\
                 made. \n\
                 This works only for the complex transform types!\n"

#define TRANSFORM_INPUT_REAL_RADIX2 "\
Input:\n\
      data ... an array of real numbers\n\
\n\
Output:\n\
      the transformed data in its special storage. Halfcomplex data\n\
      in an real array. Use halfcomplex_radix2_unpack to transform it\n\
      into an approbriate complex array.\n\
"

#define TRANSFORM_INPUT_HALFCOMPLEX "\
Input:\n\
      data ... an array of complex numbers\n\
\n\
Optional Input:\n\
      If these objects are not provided, they will be generated by the\n\
      function automatically.\n\
\n\
      n      ... length of the real array. From the complex input I can not\n\
                 compute the original length if it was odd or even. Thus I \n\
                 allow to give the input here. If not given the routine will guess\n\
                 the input length. If the last imaginary part is zero it will\n\
                 assume an real output array of even length\n\
      space  ... a workspace of approbriate type and size\n\
      table  ... a wavetable of approbriate type and size\n\
      eps    ... epsilon to use in the comparisons (default 1e-8)\n\
"

#define TRANSFORM_INPUT_HALFCOMPLEX_RADIX2 "\
Input:\n\
      data ... an array of real data containing the complex data\n\
               as required by this transform. See the GSL Reference Document\n\
\n\
"

static const char cf_doc[] = "\
Complex forward transform\n\
" TRANSFORM_INPUT;

static const char cb_doc[] = "\
Complex backward transform\n\
\n\
The output is not scaled!\n\
" TRANSFORM_INPUT;

static const char ci_doc[] = "\
Complex inverse transform\n\
\n\
The output is to scale.\n\
" TRANSFORM_INPUT;

static const char cf_doc_r2[] = "\
Complex forward radix2 transform\n\
" TRANSFORM_INPUT_RADIX2;

static const char cb_doc_r2[] = "\
Complex backward radix2 transform\n\
\n\
The output is not scaled!\n\
" TRANSFORM_INPUT_RADIX2;

static const char ci_doc_r2[] = "\
Complex inverse radix2 transform\n\
\n\
The output is to scale.\n\
" TRANSFORM_INPUT_RADIX2;

static const char cf_doc_r2_dif[] = "\
Complex forward radix2 decimation-in-frequency transform\n\
" TRANSFORM_INPUT_RADIX2;

static const char cb_doc_r2_dif[] = "\
Complex backward radix2 decimation-in-frequency transform\n\
\n\
The output is not scaled!\n\
" TRANSFORM_INPUT_RADIX2;

static const char ci_doc_r2_dif[] = "\
Complex inverse radix2 decimation-in-frequency transform\n\
\n\
The output is to scale.\n\
" TRANSFORM_INPUT_RADIX2;

static const char rt_doc[] = "\
Real transform\n\
" TRANSFORM_INPUT_REAL;

static const char hc_doc[] = "\
Half complex transform\n\
\n\
The output is not scaled!\n\
" TRANSFORM_INPUT_HALFCOMPLEX;

static const char hi_doc[] = "\
Half complex inverse\n\
" TRANSFORM_INPUT_HALFCOMPLEX;

static const char rt_doc_r2[] = "\
Real radix2 transform\n\
" TRANSFORM_INPUT_REAL_RADIX2;

static const char hc_doc_r2[] = "\
Half complex  radix2 transform\n\
\n\
The output is not scaled!\n\
" TRANSFORM_INPUT_HALFCOMPLEX_RADIX2;

static const char hi_doc_r2[] = "\
Half complex  radix2 inverse\n\
" TRANSFORM_INPUT_HALFCOMPLEX_RADIX2;

static const char un_doc_r2[] = "\
Unpack the frequency data from the output of a real radix 2 transform to an approbriate complex array.\n\
";

static PyMethodDef fftMethods[] = {
	{"complex_workspace",     PyGSL_fft_space_init_COMPLEX_WORKSPACE,      METH_VARARGS, (char*)cws_doc},
	{"complex_wavetable",     PyGSL_fft_space_init_COMPLEX_WAVETABLE,      METH_VARARGS, (char*)cwt_doc},
	{"real_workspace",        PyGSL_fft_space_init_REAL_WORKSPACE,         METH_VARARGS, (char*)rws_doc},
	{"real_wavetable",        PyGSL_fft_space_init_REAL_WAVETABLE,         METH_VARARGS, (char*)rwt_doc},
	{"halfcomplex_wavetable", PyGSL_fft_space_init_HALFCOMPLEX_WAVETABLE,  METH_VARARGS, (char*)hcwt_doc},
	{"complex_workspace_float",     PyGSL_fft_space_init_COMPLEX_WORKSPACE_FLOAT,      METH_VARARGS, (char*)cws_doc},
	{"complex_wavetable_float",     PyGSL_fft_space_init_COMPLEX_WAVETABLE_FLOAT,      METH_VARARGS, (char*)cwt_doc},
	{"real_workspace_float",        PyGSL_fft_space_init_REAL_WORKSPACE_FLOAT,         METH_VARARGS, (char*)rws_doc},
	{"real_wavetable_float",        PyGSL_fft_space_init_REAL_WAVETABLE_FLOAT,         METH_VARARGS, (char*)rwt_doc},
	{"halfcomplex_wavetable_float", PyGSL_fft_space_init_HALFCOMPLEX_WAVETABLE_FLOAT,  METH_VARARGS, (char*)hcwt_doc},
	{"complex_forward",             PyGSL_complex_fft_forward,             METH_VARARGS, (char*)cf_doc},	
	{"complex_backward",            PyGSL_complex_fft_backward,            METH_VARARGS, (char*)cb_doc},	
	{"complex_inverse",             PyGSL_complex_fft_inverse,             METH_VARARGS, (char*)ci_doc},	
	{"complex_radix2_forward",      PyGSL_complex_fft_radix2_forward,      METH_VARARGS, (char*)cf_doc_r2},	
	{"complex_radix2_backward",     PyGSL_complex_fft_radix2_backward,     METH_VARARGS, (char*)cb_doc_r2},	
	{"complex_radix2_inverse",      PyGSL_complex_fft_radix2_inverse,      METH_VARARGS, (char*)ci_doc_r2},	
	{"complex_radix2_dif_forward",  PyGSL_complex_fft_radix2_dif_forward,  METH_VARARGS, (char*)cf_doc_r2_dif},	
	{"complex_radix2_dif_backward", PyGSL_complex_fft_radix2_dif_backward, METH_VARARGS, (char*)cb_doc_r2_dif},	
	{"complex_radix2_dif_inverse",  PyGSL_complex_fft_radix2_dif_inverse,  METH_VARARGS, (char*)ci_doc_r2_dif},	
	{"real_transform",              PyGSL_real_fft_transform,              METH_VARARGS, (char*)rt_doc},	
	{"halfcomplex_transform",       PyGSL_halfcomplex_fft_transform,       METH_VARARGS, (char*)hc_doc},
	{"halfcomplex_inverse",         PyGSL_halfcomplex_fft_inverse,         METH_VARARGS, (char*)hi_doc},
	{"real_radix2_transform",       PyGSL_real_fft_radix2_transform,       METH_VARARGS, (char*)rt_doc_r2},	
	{"halfcomplex_radix2_transform",PyGSL_halfcomplex_fft_radix2_transform,METH_VARARGS, (char*)hc_doc_r2},
	{"halfcomplex_radix2_inverse",  PyGSL_halfcomplex_fft_radix2_inverse,  METH_VARARGS, (char*)hi_doc_r2},
	{"halfcomplex_radix2_unpack",   PyGSL_fft_halfcomplex_radix2_unpack,   METH_VARARGS, (char*)un_doc_r2},
	{NULL, NULL} /* Sentinel */
};

DL_EXPORT(void) initfft(void)
{
     	PyObject *m = NULL, *dict = NULL, *item = NULL;
	
	PyGSL_fft_space_pytype.ob_type = &PyType_Type;

	m = Py_InitModule("fft", fftMethods);
	module = m;
	import_array();
	init_pygsl();
	if (m == NULL)
		return;

	dict = PyModule_GetDict(m);
	if (dict == NULL)
		return;
	
	if (!(item = PyString_FromString(fft_module_doc))){
		PyErr_SetString(PyExc_ImportError, 
				"I could not generate module doc string!");
		return;
	}
	if (PyDict_SetItemString(dict, "__doc__", item) != 0){
		PyErr_SetString(PyExc_ImportError, 
				"I could not init doc string!");
		return;
	}

	return;
}


/*
 * Local Variables:
 * mode: C
 * c-file-style: "python"
 * End:
 */
