/* Odeint solver */
#include <pygsl/utils.h>
#include <pygsl/block_helpers.h>
#include <pygsl/error_helpers.h>
#include <Python.h>
#include <gsl/gsl_odeiv.h>
#include <gsl/gsl_errno.h>

char odeiv_module_doc[] = "XXX odeiv module doc missing!\n";

static char this_file[] = __FILE__;
static PyObject *module = NULL; /* set by initodeiv */ 

static void			/* generic instance destruction */
generic_dealloc (PyObject *self)
{
  DEBUG_MESS(1, " *** generic_dealloc %p\n", (void *) self);
  PyMem_Free(self);
}

typedef struct {
     PyObject_HEAD
     gsl_odeiv_step * step;
     gsl_odeiv_system system;
     PyObject *py_func;
     PyObject *py_jac;
     PyObject *arguments;
     jmp_buf buffer;
}
PyGSL_odeiv_step;

typedef struct {
  PyObject_HEAD
  PyGSL_odeiv_step * step;
  gsl_odeiv_control * control;
} PyGSL_odeiv_control;

typedef struct {
  PyObject_HEAD
  PyGSL_odeiv_step * step;
  PyGSL_odeiv_control * control;
  gsl_odeiv_evolve * evolve;
} PyGSL_odeiv_evolve;

typedef struct {
  PyObject_HEAD
  gsl_odeiv_step_type * step_type;
} PyGSL_odeiv_step_type;

typedef struct {
  PyObject_HEAD
  gsl_odeiv_control_type * control_type;
} PyGSL_odeiv_control_type;

/*---------------------------------------------------------------------------
 * Declaration of the various Methods
 *---------------------------------------------------------------------------*/
/*
 * stepper
 */
static int 
PyGSL_odeiv_func(double t, const double y[], double f[], void *params);
static int 
PyGSL_odeiv_jac(double t, const double y[], double *dfdy, double dfdt[], 
		void *params);
static PyObject *
PyGSL_odeiv_step_apply(PyGSL_odeiv_step *self, PyObject *args);
static PyObject *
PyGSL_odeiv_step_reset(PyGSL_odeiv_step *self, PyObject *args);
static void 
PyGSL_odeiv_step_free(PyGSL_odeiv_step * self);
static PyObject *
PyGSL_odeiv_step_name(PyGSL_odeiv_step *self, PyObject *args);
static PyObject *
PyGSL_odeiv_step_order(PyGSL_odeiv_step *self, PyObject *args);

/*
 * control 
 */
static PyObject *
PyGSL_odeiv_control_hadjust(PyGSL_odeiv_control *self, PyObject *args);
static void 
PyGSL_odeiv_control_free(PyGSL_odeiv_control * self);
static PyObject *
PyGSL_odeiv_control_name(PyGSL_odeiv_control *self, PyObject *args);

/*
 * evolve
 */
static void 
PyGSL_odeiv_evolve_free(PyGSL_odeiv_evolve * self);
static PyObject *
PyGSL_odeiv_evolve_apply(PyGSL_odeiv_evolve *self, PyObject *args);
static PyObject *
PyGSL_odeiv_evolve_reset(PyGSL_odeiv_evolve *self, PyObject *args);
/*---------------------------------------------------------------------------*/

static char PyGSL_odeiv_step_type_doc[] = "A odeiv step type\n";
static char PyGSL_odeiv_control_type_doc[] = "A odeiv control type\n";
static char PyGSL_odeiv_evolve_type_doc[] = "A odeiv evolve type\n";







#define PyGSL_ODEIV_GENERIC_TYPE_PYTYPE_ALL                               \
static PyTypeObject PyGSL_ODEIV_GENERIC_TYPE_PYTYPE = {		          \
  PyObject_HEAD_INIT(NULL)	/* fix up the type slot in initodeiv */	  \
  0,				/* ob_size */				  \
  PyGSL_ODEIV_GENERIC_TYPE_NAME,     	/* tp_name */			  \
  sizeof(PyGSL_ODEIV_GENERIC_TYPE),       /* tp_basicsize */		  \
  0,				/* tp_itemsize */			  \
									  \
  /* standard methods */						  \
  (destructor)  generic_dealloc,   /* tp_dealloc  ref-count==0  */	  \
  (printfunc)   0,		   /* tp_print    "print x"     */	  \
  (getattrfunc) 0,                 /* tp_getattr  "x.attr"      */	  \
  (setattrfunc) 0,		   /* tp_setattr  "x.attr=v"    */	  \
  (cmpfunc)     0,		   /* tp_compare  "x > y"       */	  \
  (reprfunc)    0,                 /* tp_repr     `x`, print x  */	  \
									  \
  /* type categories */							  \
  0,				/* tp_as_number   +,-,*,/,%,&,>>,pow...*/ \
  0,				/* tp_as_sequence +,[i],[i:j],len, ...*/  \
  0,				/* tp_as_mapping  [key], len, ...*/	  \
									  \
  /* more methods */							  \
  (hashfunc)     0,		/* tp_hash    "dict[x]" */		  \
  (ternaryfunc)  0,             /* tp_call    "x()"     */		  \
  (reprfunc)     0,             /* tp_str     "str(x)"  */		  \
  (getattrofunc) 0,		/* tp_getattro */			  \
  (setattrofunc) 0,		/* tp_setattro */			  \
  0,				/* tp_as_buffer */			  \
  0L,				/* tp_flags */				  \
  PyGSL_ODEIV_GENERIC_TYPE_DOC       /* tp_doc */                         \
};

#define PyGSL_ODEIV_GENERIC_TYPE        PyGSL_odeiv_step_type
#define PyGSL_ODEIV_GENERIC_TYPE_PYTYPE PyGSL_odeiv_step_type_pytype
#define PyGSL_ODEIV_GENERIC_TYPE_NAME   "PyGSL_odeiv_step_type"
#define PyGSL_ODEIV_GENERIC_TYPE_DOC    PyGSL_odeiv_step_type_doc
PyGSL_ODEIV_GENERIC_TYPE_PYTYPE_ALL


#undef PyGSL_ODEIV_GENERIC_TYPE       
#undef PyGSL_ODEIV_GENERIC_TYPE_PYTYPE
#undef PyGSL_ODEIV_GENERIC_TYPE_NAME  
#undef PyGSL_ODEIV_GENERIC_TYPE_DOC   
#define PyGSL_ODEIV_GENERIC_TYPE        PyGSL_odeiv_control_type
#define PyGSL_ODEIV_GENERIC_TYPE_PYTYPE PyGSL_odeiv_control_type_pytype
#define PyGSL_ODEIV_GENERIC_TYPE_NAME   "PyGSL_odeiv_control_type"
#define PyGSL_ODEIV_GENERIC_TYPE_DOC    PyGSL_odeiv_control_type_doc
PyGSL_ODEIV_GENERIC_TYPE_PYTYPE_ALL



#define PyGSLOdeivStepType_Check(v)    ((v)->ob_type == &PyGSL_odeiv_step_type_pytype)
#define PyGSLOdeivControlType_Check(v) ((v)->ob_type == &PyGSL_odeiv_control_type_pytype)
#define PyGSLOdeivEvolveType_Check(v)  ((v)->ob_type == &PyGSL_odeiv_evolve_type_pytype)





#define PyGSL_ODEIV_GENERIC_ALL                                                           \
static PyObject *									  \
PyGSL_ODEIV_GENERIC_GETATTR(PyGSL_ODEIV_GENERIC *self, char *name)		          \
{											  \
     PyObject *tmp = NULL;								  \
											  \
     FUNC_MESS_BEGIN();									  \
 											  \
     tmp = Py_FindMethod(PyGSL_ODEIV_GENERIC_METHODS, (PyObject *) self, name);	          \
     if(NULL == tmp){	  								  \
	  PyGSL_add_traceback(module, __FILE__, "odeiv.__attr__", __LINE__ - 1);	  \
	  return NULL;									  \
     }											  \
     return tmp;                                                                          \
}                                                                                         \
static PyTypeObject PyGSL_ODEIV_GENERIC_PYTYPE = {					  \
  PyObject_HEAD_INIT(NULL)	/* fix up the type slot in initcrng */			  \
  0,				/* ob_size */						  \
  PyGSL_ODEIV_GENERIC_NAME,			/* tp_name */			          \
  sizeof(PyGSL_ODEIV_GENERIC),  /* tp_basicsize */					  \
  0,				/* tp_itemsize */					  \
											  \
  /* standard methods */								  \
  (destructor)  PyGSL_ODEIV_GENERIC_DELETE,       /* tp_dealloc  ref-count==0  */	  \
  (printfunc)   0,		                      /* tp_print    "print x"     */	  \
  (getattrfunc) PyGSL_ODEIV_GENERIC_GETATTR,       /* tp_getattr  "x.attr"      */	  \
  (setattrfunc) 0,		   /* tp_setattr  "x.attr=v"    */			  \
  (cmpfunc)     0,		   /* tp_compare  "x > y"       */			  \
  (reprfunc)    0,                 /* tp_repr     `x`, print x  */			  \
											  \
  /* type categories */									  \
  0,				/* tp_as_number   +,-,*,/,%,&,>>,pow...*/		  \
  0,				/* tp_as_sequence +,[i],[i:j],len, ...*/		  \
  0,				/* tp_as_mapping  [key], len, ...*/			  \
											  \
  /* more methods */									  \
  (hashfunc)     0,		/* tp_hash    "dict[x]" */				  \
  (ternaryfunc)  0,             /* tp_call    "x()"     */				  \
  (reprfunc)     0,             /* tp_str     "str(x)"  */				  \
  (getattrofunc) 0,		/* tp_getattro */					  \
  (setattrofunc) 0,		/* tp_setattro */					  \
  0,				/* tp_as_buffer */					  \
  0L,				/* tp_flags */						  \
  PyGSL_ODEIV_GENERIC_DOC       /* doc */                                                 \
};                                                                                        


#define PyGSL_ODEIV_GENERIC            PyGSL_odeiv_step
#define PyGSL_ODEIV_GENERIC_NAME      "PyGSL_odeiv_step"
#define PyGSL_ODEIV_GENERIC_PYTYPE     PyGSL_odeiv_step_pytype
#define PyGSL_ODEIV_GENERIC_DOC        PyGSL_odeiv_step_doc
#define PyGSL_ODEIV_GENERIC_GETATTR    PyGSL_odeiv_step_getattr
#define PyGSL_ODEIV_GENERIC_METHODS    PyGSL_odeiv_step_methods
#define PyGSL_ODEIV_GENERIC_DELETE     PyGSL_odeiv_step_free
PyGSL_ODEIV_GENERIC_ALL
/**/;
#undef PyGSL_ODEIV_GENERIC       
#undef PyGSL_ODEIV_GENERIC_NAME  
#undef PyGSL_ODEIV_GENERIC_PYTYPE
#undef PyGSL_ODEIV_GENERIC_DOC   
#undef PyGSL_ODEIV_GENERIC_GETATTR
#undef PyGSL_ODEIV_GENERIC_METHODS
#undef PyGSL_ODEIV_GENERIC_DELETE
#define PyGSL_ODEIV_GENERIC            PyGSL_odeiv_control
#define PyGSL_ODEIV_GENERIC_NAME      "PyGSL_odeiv_control"
#define PyGSL_ODEIV_GENERIC_PYTYPE     PyGSL_odeiv_control_pytype
#define PyGSL_ODEIV_GENERIC_DOC        PyGSL_odeiv_control_doc
#define PyGSL_ODEIV_GENERIC_GETATTR    PyGSL_odeiv_control_getattr
#define PyGSL_ODEIV_GENERIC_METHODS    PyGSL_odeiv_control_methods
#define PyGSL_ODEIV_GENERIC_DELETE     PyGSL_odeiv_control_free
PyGSL_ODEIV_GENERIC_ALL
/**/;
#undef PyGSL_ODEIV_GENERIC       
#undef PyGSL_ODEIV_GENERIC_NAME  
#undef PyGSL_ODEIV_GENERIC_PYTYPE
#undef PyGSL_ODEIV_GENERIC_DOC   
#undef PyGSL_ODEIV_GENERIC_GETATTR
#undef PyGSL_ODEIV_GENERIC_METHODS
#undef PyGSL_ODEIV_GENERIC_DELETE
#define PyGSL_ODEIV_GENERIC            PyGSL_odeiv_evolve
#define PyGSL_ODEIV_GENERIC_NAME      "PyGSL_odeiv_evolve"
#define PyGSL_ODEIV_GENERIC_PYTYPE     PyGSL_odeiv_evolve_pytype
#define PyGSL_ODEIV_GENERIC_DOC        PyGSL_odeiv_evolve_doc
#define PyGSL_ODEIV_GENERIC_GETATTR    PyGSL_odeiv_evolve_getattr
#define PyGSL_ODEIV_GENERIC_METHODS    PyGSL_odeiv_evolve_methods
#define PyGSL_ODEIV_GENERIC_DELETE     PyGSL_odeiv_evolve_free
PyGSL_ODEIV_GENERIC_ALL
/**/;





static void 
PyGSL_odeiv_step_free(PyGSL_odeiv_step * self)
{
     assert(PyGSL_ODEIV_STEP_Check(self));
     Py_DECREF(self->py_func);
     Py_XDECREF(self->py_jac);
     Py_DECREF(self->arguments);
     gsl_odeiv_step_free(self->step);
     PyMem_Free(self);
}

static PyObject *
PyGSL_odeiv_step_reset(PyGSL_odeiv_step *self, PyObject *args)
{
     assert(PyGSL_ODEIV_STEP_Check(self));
     gsl_odeiv_step_reset(self->step);
     Py_INCREF(Py_None);
     return Py_None;
}

static PyObject *
PyGSL_odeiv_step_name(PyGSL_odeiv_step *self, PyObject *args)
{
     assert(PyGSL_ODEIV_STEP_Check(self));
     return PyString_FromString(gsl_odeiv_step_name(self->step));
}

{
     assert(PyGSL_ODEIV_STEP_Check(self));
     return PyInt_FromLong((long) gsl_odeiv_step_order(self->step));
}


/* --------------------------------------------------------------------------- */
/* control_hadjust needs a few arrays */
/*
extern int 
gsl_odeiv_control_hadjust (gsl_odeiv_control * c, gsl_odeiv_step * s, 
			   const double y0[],  const double yerr[], 
			   const double dydt[], double * h);
*/


static void 
PyGSL_odeiv_control_free(PyGSL_odeiv_control * self)
{
     assert(PyGSL_ODEIV_CONTROL_Check(self));
     Py_DECREF(self->step);
     //gsl_odeiv_control_free(self->control);
     PyMem_Free(self);
}

static PyObject *
PyGSL_odeiv_control_name(PyGSL_odeiv_control *self, PyObject *args)
{
     assert(PyGSL_ODEIV_CONTROL_Check(self));
     return PyString_FromString(gsl_odeiv_control_name(self->control));
}

static void 
PyGSL_odeiv_evolve_free(PyGSL_odeiv_evolve * self)
{
     assert(PyGSL_ODEIV_EVOLVE_Check(self));
     Py_DECREF(self->step);
     Py_DECREF(self->control);
     gsl_odeiv_evolve_free(self->evolve);
     PyMem_Free(self);
}

static PyObject *
PyGSL_odeiv_evolve_reset(PyGSL_odeiv_evolve *self, PyObject *args)
{
     assert(PyGSL_ODEIV_EVOLVE_Check(self));
     gsl_odeiv_evolve_reset(self->evolve);
     Py_INCREF(Py_None);
     return Py_None;
}


#if 0
static
void create_odeiv_step_types(PyObject *module_dict)
{

     PyGSL_odeiv_step_type *a_odeiv_step = NULL;
     PyObject *item=NULL;

     gsl_odeiv_step_type ** thistype;
     gsl_odeiv_step_type const * const step_types[]  ={
	  gsl_odeiv_step_rk2,
	  gsl_odeiv_step_rk4,
	  gsl_odeiv_step_rkf45,
	  gsl_odeiv_step_rkck,
	  gsl_odeiv_step_rk8pd,
	  gsl_odeiv_step_rk2imp,
	  gsl_odeiv_step_rk4imp,
	  gsl_odeiv_step_bsimp,
	  gsl_odeiv_step_gear1,
	  gsl_odeiv_step_gear2,
	  NULL
     };

     FUNC_MESS_BEGIN();

     thistype = (gsl_odeiv_step_type **) step_types;
     while((*thistype) != NULL){
	  a_odeiv_step =  PyObject_NEW(PyGSL_odeiv_step_type, &PyGSL_odeiv_step_type_pytype);
	  assert(a_odeiv_step);
	  a_odeiv_step->step_type = (gsl_odeiv_step_type *) *thistype;
	  item = PyString_FromString((*thistype)->name);
	  DEBUG_MESS(2, "Preparing step type -->%s<--", PyString_AsString(item));
	  PyGSL_clear_name(PyString_AsString(item), PyString_Size(item));
	  DEBUG_MESS(2, "Adding step type -->%s<--",  PyString_AsString(item));
	  assert(item);
	  PyDict_SetItem(module_dict, item, (PyObject *) a_odeiv_step);
	  /* Py_DECREF(item); */
	  item = NULL;	  
	  thistype++;

     }
     FUNC_MESS_END();
}
#endif


static PyMethodDef PyGSL_odeiv_module_functions[] = {
     {"step_rk2",    PyGSL_odeiv_step_init_rk2,    METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_rk4",    PyGSL_odeiv_step_init_rk4,    METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_rkf45",  PyGSL_odeiv_step_init_rkf45,  METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_rkck",   PyGSL_odeiv_step_init_rkck,   METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_rk8pd",  PyGSL_odeiv_step_init_rk8pd,  METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_rk2imp", PyGSL_odeiv_step_init_rk2imp, METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_rk4imp", PyGSL_odeiv_step_init_rk4imp, METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_bsimp",  PyGSL_odeiv_step_init_bsimp,  METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_gear1",  PyGSL_odeiv_step_init_gear1,  METH_VARARGS|METH_KEYWORDS, NULL},
     {"step_gear2",  PyGSL_odeiv_step_init_gear2,  METH_VARARGS|METH_KEYWORDS, NULL},
     {"control_standard_new", PyGSL_odeiv_control_init_standard_new, METH_VARARGS, NULL},
     {"control_y_new",        PyGSL_odeiv_control_init_y_new,        METH_VARARGS, NULL},
     {"control_yp_new",       PyGSL_odeiv_control_init_yp_new,       METH_VARARGS, NULL},
     {"evolve", PyGSL_odeiv_evolve_init, METH_VARARGS, NULL},
     {NULL, NULL, 0}        /* Sentinel */
};

void 
initodeiv(void)
{
     PyObject *m=NULL, *item=NULL, *dict=NULL;

     FUNC_MESS_BEGIN();
     fprintf(stderr, "Compiled at %s %s\n", __DATE__, __TIME__);
     m = Py_InitModule("odeiv", PyGSL_odeiv_module_functions);
     assert(m);
     module = m;
     import_array();
     init_pygsl();

     PyGSL_odeiv_step_type_pytype.ob_type = &PyType_Type;
     PyGSL_odeiv_control_type_pytype.ob_type = &PyType_Type;

     PyGSL_odeiv_step_pytype.ob_type = &PyType_Type;
     PyGSL_odeiv_control_pytype.ob_type = &PyType_Type;
     PyGSL_odeiv_evolve_pytype.ob_type = &PyType_Type;

     dict = PyModule_GetDict(m);
     /* create_odeiv_step_types(dict); */
     if(!dict)
	  goto fail;
     
     if (!(item = PyString_FromString(odeiv_module_doc))){
	  PyErr_SetString(PyExc_ImportError, 
			  "I could not generate module doc string!");
	  goto fail;
     }
     if (PyDict_SetItemString(dict, "__doc__", item) != 0){
	  PyErr_SetString(PyExc_ImportError, 
			  "I could not init doc string!");
	  goto fail;
     }
     
     FUNC_MESS_END();
     return;
 fail:
     FUNC_MESS("Fail");
     fprintf(stderr, "Import of module odeiv failed!\n");
}

