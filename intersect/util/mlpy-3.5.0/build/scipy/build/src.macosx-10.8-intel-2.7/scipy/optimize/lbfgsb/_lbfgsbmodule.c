/* File: _lbfgsbmodule.c
 * This file is auto-generated with f2py (version:2).
 * f2py is a Fortran to Python Interface Generator (FPIG), Second Edition,
 * written by Pearu Peterson <pearu@cens.ioc.ee>.
 * See http://cens.ioc.ee/projects/f2py2e/
 * Generation date: Thu Sep  6 15:26:17 2012
 * $Revision:$
 * $Date:$
 * Do not edit this file directly unless you know what you are doing!!!
 */
#ifdef __cplusplus
extern "C" {
#endif

/*********************** See f2py2e/cfuncs.py: includes ***********************/
#include "Python.h"
#include <stdarg.h>
#include "fortranobject.h"
#include <string.h>
#include <math.h>

/**************** See f2py2e/rules.py: mod_rules['modulebody'] ****************/
static PyObject *_lbfgsb_error;
static PyObject *_lbfgsb_module;

/*********************** See f2py2e/cfuncs.py: typedefs ***********************/
typedef char * string;

/****************** See f2py2e/cfuncs.py: typedefs_generated ******************/
/*need_typedefs_generated*/

/********************** See f2py2e/cfuncs.py: cppmacros **********************/
#define STRINGMALLOC(str,len)\
  if ((str = (string)malloc(sizeof(char)*(len+1))) == NULL) {\
    PyErr_SetString(PyExc_MemoryError, "out of memory");\
    goto capi_fail;\
  } else {\
    (str)[len] = '\0';\
  }

\
#define FAILNULL(p) do {                                            \
    if ((p) == NULL) {                                              \
        PyErr_SetString(PyExc_MemoryError, "NULL pointer found");   \
        goto capi_fail;                                             \
    }                                                               \
} while (0)

#define PRINTPYOBJERR(obj)\
  fprintf(stderr,"_lbfgsb.error is related to ");\
  PyObject_Print((PyObject *)obj,stderr,Py_PRINT_RAW);\
  fprintf(stderr,"\n");

#define pyobj_from_double1(v) (PyFloat_FromDouble(v))
#if defined(PREPEND_FORTRAN)
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F
#else
#define F_FUNC(f,F) _##f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F##_
#else
#define F_FUNC(f,F) _##f##_
#endif
#endif
#else
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F
#else
#define F_FUNC(f,F) f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F##_
#else
#define F_FUNC(f,F) f##_
#endif
#endif
#endif
#if defined(UNDERSCORE_G77)
#define F_FUNC_US(f,F) F_FUNC(f##_,F##_)
#else
#define F_FUNC_US(f,F) F_FUNC(f,F)
#endif

#define rank(var) var ## _Rank
#define shape(var,dim) var ## _Dims[dim]
#define old_rank(var) (((PyArrayObject *)(capi_ ## var ## _tmp))->nd)
#define old_shape(var,dim) (((PyArrayObject *)(capi_ ## var ## _tmp))->dimensions[dim])
#define fshape(var,dim) shape(var,rank(var)-dim-1)
#define len(var) shape(var,0)
#define flen(var) fshape(var,0)
#define old_size(var) PyArray_SIZE((PyArrayObject *)(capi_ ## var ## _tmp))
/* #define index(i) capi_i ## i */
#define slen(var) capi_ ## var ## _len
#define size(var, ...) f2py_size((PyArrayObject *)(capi_ ## var ## _tmp), ## __VA_ARGS__, -1)

#define STRINGFREE(str) do {if (!(str == NULL)) free(str);} while (0)

#define CHECKSCALAR(check,tcheck,name,show,var)\
  if (!(check)) {\
    char errstring[256];\
    sprintf(errstring, "%s: "show, "("tcheck") failed for "name, var);\
    PyErr_SetString(_lbfgsb_error,errstring);\
    /*goto capi_fail;*/\
  } else 
#ifdef DEBUGCFUNCS
#define CFUNCSMESS(mess) fprintf(stderr,"debug-capi:"mess);
#define CFUNCSMESSPY(mess,obj) CFUNCSMESS(mess) \
  PyObject_Print((PyObject *)obj,stderr,Py_PRINT_RAW);\
  fprintf(stderr,"\n");
#else
#define CFUNCSMESS(mess)
#define CFUNCSMESSPY(mess,obj)
#endif

#ifndef max
#define max(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a < b) ? (a) : (b))
#endif

#define STRINGCOPYN(to,from,buf_size)                           \
    do {                                                        \
        int _m = (buf_size);                                    \
        char *_to = (to);                                       \
        char *_from = (from);                                   \
        FAILNULL(_to); FAILNULL(_from);                         \
        (void)strncpy(_to, _from, sizeof(char)*_m);             \
        _to[_m-1] = '\0';                                      \
        /* Padding with spaces instead of nulls */              \
        for (_m -= 2; _m >= 0 && _to[_m] == '\0'; _m--) {      \
            _to[_m] = ' ';                                      \
        }                                                       \
    } while (0)

/* New SciPy */
#define TRYPYARRAYTEMPLATECHAR case PyArray_STRING: *(char *)(arr->data)=*v; break;
#define TRYPYARRAYTEMPLATELONG case PyArray_LONG: *(long *)(arr->data)=*v; break;
#define TRYPYARRAYTEMPLATEOBJECT case PyArray_OBJECT: (arr->descr->f->setitem)(pyobj_from_ ## ctype ## 1(*v),arr->data); break;

#define TRYPYARRAYTEMPLATE(ctype,typecode) \
        PyArrayObject *arr = NULL;\
        if (!obj) return -2;\
        if (!PyArray_Check(obj)) return -1;\
        if (!(arr=(PyArrayObject *)obj)) {fprintf(stderr,"TRYPYARRAYTEMPLATE:");PRINTPYOBJERR(obj);return 0;}\
        if (arr->descr->type==typecode)  {*(ctype *)(arr->data)=*v; return 1;}\
        switch (arr->descr->type_num) {\
                case PyArray_DOUBLE: *(double *)(arr->data)=*v; break;\
                case PyArray_INT: *(int *)(arr->data)=*v; break;\
                case PyArray_LONG: *(long *)(arr->data)=*v; break;\
                case PyArray_FLOAT: *(float *)(arr->data)=*v; break;\
                case PyArray_CDOUBLE: *(double *)(arr->data)=*v; break;\
                case PyArray_CFLOAT: *(float *)(arr->data)=*v; break;\
                case PyArray_BOOL: *(npy_bool *)(arr->data)=(*v!=0); break;\
                case PyArray_UBYTE: *(unsigned char *)(arr->data)=*v; break;\
                case PyArray_BYTE: *(signed char *)(arr->data)=*v; break;\
                case PyArray_SHORT: *(short *)(arr->data)=*v; break;\
                case PyArray_USHORT: *(npy_ushort *)(arr->data)=*v; break;\
                case PyArray_UINT: *(npy_uint *)(arr->data)=*v; break;\
                case PyArray_ULONG: *(npy_ulong *)(arr->data)=*v; break;\
                case PyArray_LONGLONG: *(npy_longlong *)(arr->data)=*v; break;\
                case PyArray_ULONGLONG: *(npy_ulonglong *)(arr->data)=*v; break;\
                case PyArray_LONGDOUBLE: *(npy_longdouble *)(arr->data)=*v; break;\
                case PyArray_CLONGDOUBLE: *(npy_longdouble *)(arr->data)=*v; break;\
                case PyArray_OBJECT: (arr->descr->f->setitem)(pyobj_from_ ## ctype ## 1(*v),arr->data, arr); break;\
        default: return -2;\
        };\
        return 1


/************************ See f2py2e/cfuncs.py: cfuncs ************************/
int f2py_size(PyArrayObject* var, ...)
{
  npy_int sz = 0;
  npy_int dim;
  npy_int rank;
  va_list argp;
  va_start(argp, var);
  dim = va_arg(argp, npy_int);
  if (dim==-1)
    {
      sz = PyArray_SIZE(var);
    }
  else
    {
      rank = PyArray_NDIM(var);
      if (dim>=1 && dim<=rank)
        sz = PyArray_DIM(var, dim-1);
      else
        fprintf(stderr, "f2py_size: 2nd argument value=%d fails to satisfy 1<=value<=%d. Result will be 0.\n", dim, rank);
    }
  va_end(argp);
  return sz;
}

static int try_pyarr_from_double(PyObject* obj,double* v) {
  TRYPYARRAYTEMPLATE(double,'d');
}

static int try_pyarr_from_string(PyObject *obj,const string str) {
  PyArrayObject *arr = NULL;
  if (PyArray_Check(obj) && (!((arr = (PyArrayObject *)obj) == NULL)))
    { STRINGCOPYN(arr->data,str,PyArray_NBYTES(arr)); }
  return 1;
capi_fail:
  PRINTPYOBJERR(obj);
  PyErr_SetString(_lbfgsb_error,"try_pyarr_from_string failed");
  return 0;
}

static int string_from_pyobj(string *str,int *len,const string inistr,PyObject *obj,const char *errmess) {
  PyArrayObject *arr = NULL;
  PyObject *tmp = NULL;
#ifdef DEBUGCFUNCS
fprintf(stderr,"string_from_pyobj(str='%s',len=%d,inistr='%s',obj=%p)\n",(char*)str,*len,(char *)inistr,obj);
#endif
  if (obj == Py_None) {
    if (*len == -1)
      *len = strlen(inistr); /* Will this cause problems? */
    STRINGMALLOC(*str,*len);
    STRINGCOPYN(*str,inistr,*len+1);
    return 1;
  }
  if (PyArray_Check(obj)) {
    if ((arr = (PyArrayObject *)obj) == NULL)
      goto capi_fail;
    if (!ISCONTIGUOUS(arr)) {
      PyErr_SetString(PyExc_ValueError,"array object is non-contiguous.");
      goto capi_fail;
    }
    if (*len == -1)
      *len = (arr->descr->elsize)*PyArray_SIZE(arr);
    STRINGMALLOC(*str,*len);
    STRINGCOPYN(*str,arr->data,*len+1);
    return 1;
  }
  if (PyString_Check(obj)) {
    tmp = obj;
    Py_INCREF(tmp);
  }
#if PY_VERSION_HEX >= 0x03000000
  else if (PyUnicode_Check(obj)) {
    tmp = PyUnicode_AsASCIIString(obj);
  }
  else {
    PyObject *tmp2;
    tmp2 = PyObject_Str(obj);
    if (tmp2) {
      tmp = PyUnicode_AsASCIIString(tmp2);
      Py_DECREF(tmp2);
    }
    else {
      tmp = NULL;
    }
  }
#else
  else {
    tmp = PyObject_Str(obj);
  }
#endif
  if (tmp == NULL) goto capi_fail;
  if (*len == -1)
    *len = PyString_GET_SIZE(tmp);
  STRINGMALLOC(*str,*len);
  STRINGCOPYN(*str,PyString_AS_STRING(tmp),*len+1);
  Py_DECREF(tmp);
  return 1;
capi_fail:
  Py_XDECREF(tmp);
  {
    PyObject* err = PyErr_Occurred();
    if (err==NULL) err = _lbfgsb_error;
    PyErr_SetString(err,errmess);
  }
  return 0;
}

static int double_from_pyobj(double* v,PyObject *obj,const char *errmess) {
  PyObject* tmp = NULL;
  if (PyFloat_Check(obj)) {
#ifdef __sgi
    *v = PyFloat_AsDouble(obj);
#else
    *v = PyFloat_AS_DOUBLE(obj);
#endif
    return 1;
  }
  tmp = PyNumber_Float(obj);
  if (tmp) {
#ifdef __sgi
    *v = PyFloat_AsDouble(tmp);
#else
    *v = PyFloat_AS_DOUBLE(tmp);
#endif
    Py_DECREF(tmp);
    return 1;
  }
  if (PyComplex_Check(obj))
    tmp = PyObject_GetAttrString(obj,"real");
  else if (PyString_Check(obj) || PyUnicode_Check(obj))
    /*pass*/;
  else if (PySequence_Check(obj))
    tmp = PySequence_GetItem(obj,0);
  if (tmp) {
    PyErr_Clear();
    if (double_from_pyobj(v,tmp,errmess)) {Py_DECREF(tmp); return 1;}
    Py_DECREF(tmp);
  }
  {
    PyObject* err = PyErr_Occurred();
    if (err==NULL) err = _lbfgsb_error;
    PyErr_SetString(err,errmess);
  }
  return 0;
}

static int int_from_pyobj(int* v,PyObject *obj,const char *errmess) {
  PyObject* tmp = NULL;
  if (PyInt_Check(obj)) {
    *v = (int)PyInt_AS_LONG(obj);
    return 1;
  }
  tmp = PyNumber_Int(obj);
  if (tmp) {
    *v = PyInt_AS_LONG(tmp);
    Py_DECREF(tmp);
    return 1;
  }
  if (PyComplex_Check(obj))
    tmp = PyObject_GetAttrString(obj,"real");
  else if (PyString_Check(obj) || PyUnicode_Check(obj))
    /*pass*/;
  else if (PySequence_Check(obj))
    tmp = PySequence_GetItem(obj,0);
  if (tmp) {
    PyErr_Clear();
    if (int_from_pyobj(v,tmp,errmess)) {Py_DECREF(tmp); return 1;}
    Py_DECREF(tmp);
  }
  {
    PyObject* err = PyErr_Occurred();
    if (err==NULL) err = _lbfgsb_error;
    PyErr_SetString(err,errmess);
  }
  return 0;
}


/********************* See f2py2e/cfuncs.py: userincludes *********************/
/*need_userincludes*/

/********************* See f2py2e/capi_rules.py: usercode *********************/


/* See f2py2e/rules.py */
extern void F_FUNC(setulb,SETULB)(int*,int*,double*,double*,double*,int*,double*,double*,double*,double*,double*,int*,string,int*,string,int*,int*,double*,size_t,size_t);
/*eof externroutines*/

/******************** See f2py2e/capi_rules.py: usercode1 ********************/


/******************* See f2py2e/cb_rules.py: buildcallback *******************/
/*need_callbacks*/

/*********************** See f2py2e/rules.py: buildapi ***********************/

/*********************************** setulb ***********************************/
static char doc_f2py_rout__lbfgsb_setulb[] = "\
Function signature:\n\
  setulb(m,x,l,u,nbd,f,g,factr,pgtol,wa,iwa,task,iprint,csave,lsave,isave,dsave,[n])\n\
Required arguments:\n"
"  m : input int\n"
"  x : in/output rank-1 array('d') with bounds (n)\n"
"  l : input rank-1 array('d') with bounds (n)\n"
"  u : input rank-1 array('d') with bounds (n)\n"
"  nbd : input rank-1 array('i') with bounds (n)\n"
"  f : in/output rank-0 array(float,'d')\n"
"  g : in/output rank-1 array('d') with bounds (n)\n"
"  factr : input float\n"
"  pgtol : input float\n"
"  wa : in/output rank-1 array('d') with bounds (2*m*n+4*n+12*m*m+12*m)\n"
"  iwa : in/output rank-1 array('i') with bounds (3 * n)\n"
"  task : in/output rank-0 array(string(len=60),'c')\n"
"  iprint : input int\n"
"  csave : in/output rank-0 array(string(len=60),'c')\n"
"  lsave : in/output rank-1 array('i') with bounds (4)\n"
"  isave : in/output rank-1 array('i') with bounds (44)\n"
"  dsave : in/output rank-1 array('d') with bounds (29)\n"
"Optional arguments:\n"
"  n := len(x) input int";
/* extern void F_FUNC(setulb,SETULB)(int*,int*,double*,double*,double*,int*,double*,double*,double*,double*,double*,int*,string,int*,string,int*,int*,double*,size_t,size_t); */
static PyObject *f2py_rout__lbfgsb_setulb(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(int*,int*,double*,double*,double*,int*,double*,double*,double*,double*,double*,int*,string,int*,string,int*,int*,double*,size_t,size_t)) {
  PyObject * volatile capi_buildvalue = NULL;
  volatile int f2py_success = 1;
/*decl*/

  int n = 0;
  PyObject *n_capi = Py_None;
  int m = 0;
  PyObject *m_capi = Py_None;
  double *x = NULL;
  npy_intp x_Dims[1] = {-1};
  const int x_Rank = 1;
  PyArrayObject *capi_x_tmp = NULL;
  int capi_x_intent = 0;
  PyObject *x_capi = Py_None;
  double *l = NULL;
  npy_intp l_Dims[1] = {-1};
  const int l_Rank = 1;
  PyArrayObject *capi_l_tmp = NULL;
  int capi_l_intent = 0;
  PyObject *l_capi = Py_None;
  double *u = NULL;
  npy_intp u_Dims[1] = {-1};
  const int u_Rank = 1;
  PyArrayObject *capi_u_tmp = NULL;
  int capi_u_intent = 0;
  PyObject *u_capi = Py_None;
  int *nbd = NULL;
  npy_intp nbd_Dims[1] = {-1};
  const int nbd_Rank = 1;
  PyArrayObject *capi_nbd_tmp = NULL;
  int capi_nbd_intent = 0;
  PyObject *nbd_capi = Py_None;
  double f = 0;
  PyObject *f_capi = Py_None;
  double *g = NULL;
  npy_intp g_Dims[1] = {-1};
  const int g_Rank = 1;
  PyArrayObject *capi_g_tmp = NULL;
  int capi_g_intent = 0;
  PyObject *g_capi = Py_None;
  double factr = 0;
  PyObject *factr_capi = Py_None;
  double pgtol = 0;
  PyObject *pgtol_capi = Py_None;
  double *wa = NULL;
  npy_intp wa_Dims[1] = {-1};
  const int wa_Rank = 1;
  PyArrayObject *capi_wa_tmp = NULL;
  int capi_wa_intent = 0;
  PyObject *wa_capi = Py_None;
  int *iwa = NULL;
  npy_intp iwa_Dims[1] = {-1};
  const int iwa_Rank = 1;
  PyArrayObject *capi_iwa_tmp = NULL;
  int capi_iwa_intent = 0;
  PyObject *iwa_capi = Py_None;
  string task = NULL;
  int slen(task);
  PyObject *task_capi = Py_None;
  int iprint = 0;
  PyObject *iprint_capi = Py_None;
  string csave = NULL;
  int slen(csave);
  PyObject *csave_capi = Py_None;
  int *lsave = NULL;
  npy_intp lsave_Dims[1] = {-1};
  const int lsave_Rank = 1;
  PyArrayObject *capi_lsave_tmp = NULL;
  int capi_lsave_intent = 0;
  PyObject *lsave_capi = Py_None;
  int *isave = NULL;
  npy_intp isave_Dims[1] = {-1};
  const int isave_Rank = 1;
  PyArrayObject *capi_isave_tmp = NULL;
  int capi_isave_intent = 0;
  PyObject *isave_capi = Py_None;
  double *dsave = NULL;
  npy_intp dsave_Dims[1] = {-1};
  const int dsave_Rank = 1;
  PyArrayObject *capi_dsave_tmp = NULL;
  int capi_dsave_intent = 0;
  PyObject *dsave_capi = Py_None;
  static char *capi_kwlist[] = {"m","x","l","u","nbd","f","g","factr","pgtol","wa","iwa","task","iprint","csave","lsave","isave","dsave","n",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
  if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
    "OOOOOOOOOOOOOOOOO|O:_lbfgsb.setulb",\
    capi_kwlist,&m_capi,&x_capi,&l_capi,&u_capi,&nbd_capi,&f_capi,&g_capi,&factr_capi,&pgtol_capi,&wa_capi,&iwa_capi,&task_capi,&iprint_capi,&csave_capi,&lsave_capi,&isave_capi,&dsave_capi,&n_capi))
    return NULL;
/*frompyobj*/
  /* Processing variable lsave */
  lsave_Dims[0]=4;
  capi_lsave_intent |= F2PY_INTENT_INOUT;
  capi_lsave_tmp = array_from_pyobj(PyArray_INT,lsave_Dims,lsave_Rank,capi_lsave_intent,lsave_capi);
  if (capi_lsave_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 15th argument `lsave' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    lsave = (int *)(capi_lsave_tmp->data);

  /* Processing variable csave */
  slen(csave) = 60;
  f2py_success = string_from_pyobj(&csave,&slen(csave),"",csave_capi,"string_from_pyobj failed in converting 14th argument `csave' of _lbfgsb.setulb to C string");
  if (f2py_success) {
  /* Processing variable factr */
    f2py_success = double_from_pyobj(&factr,factr_capi,"_lbfgsb.setulb() 8th argument (factr) can't be converted to double");
  if (f2py_success) {
  /* Processing variable task */
  slen(task) = 60;
  f2py_success = string_from_pyobj(&task,&slen(task),"",task_capi,"string_from_pyobj failed in converting 12nd argument `task' of _lbfgsb.setulb to C string");
  if (f2py_success) {
  /* Processing variable dsave */
  dsave_Dims[0]=29;
  capi_dsave_intent |= F2PY_INTENT_INOUT;
  capi_dsave_tmp = array_from_pyobj(PyArray_DOUBLE,dsave_Dims,dsave_Rank,capi_dsave_intent,dsave_capi);
  if (capi_dsave_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 17th argument `dsave' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    dsave = (double *)(capi_dsave_tmp->data);

  /* Processing variable f */
    f2py_success = double_from_pyobj(&f,f_capi,"_lbfgsb.setulb() 6th argument (f) can't be converted to double");
  if (f2py_success) {
  /* Processing variable iprint */
    f2py_success = int_from_pyobj(&iprint,iprint_capi,"_lbfgsb.setulb() 13rd argument (iprint) can't be converted to int");
  if (f2py_success) {
  /* Processing variable m */
    f2py_success = int_from_pyobj(&m,m_capi,"_lbfgsb.setulb() 1st argument (m) can't be converted to int");
  if (f2py_success) {
  /* Processing variable isave */
  isave_Dims[0]=44;
  capi_isave_intent |= F2PY_INTENT_INOUT;
  capi_isave_tmp = array_from_pyobj(PyArray_INT,isave_Dims,isave_Rank,capi_isave_intent,isave_capi);
  if (capi_isave_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 16th argument `isave' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    isave = (int *)(capi_isave_tmp->data);

  /* Processing variable x */
  ;
  capi_x_intent |= F2PY_INTENT_INOUT;
  capi_x_tmp = array_from_pyobj(PyArray_DOUBLE,x_Dims,x_Rank,capi_x_intent,x_capi);
  if (capi_x_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 2nd argument `x' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    x = (double *)(capi_x_tmp->data);

  /* Processing variable pgtol */
    f2py_success = double_from_pyobj(&pgtol,pgtol_capi,"_lbfgsb.setulb() 9th argument (pgtol) can't be converted to double");
  if (f2py_success) {
  /* Processing variable n */
  if (n_capi == Py_None) n = len(x); else
    f2py_success = int_from_pyobj(&n,n_capi,"_lbfgsb.setulb() 1st keyword (n) can't be converted to int");
  if (f2py_success) {
  CHECKSCALAR(len(x)>=n,"len(x)>=n","1st keyword n","setulb:n=%d",n) {
  /* Processing variable u */
  u_Dims[0]=n;
  capi_u_intent |= F2PY_INTENT_IN;
  capi_u_tmp = array_from_pyobj(PyArray_DOUBLE,u_Dims,u_Rank,capi_u_intent,u_capi);
  if (capi_u_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 4th argument `u' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    u = (double *)(capi_u_tmp->data);

  /* Processing variable wa */
  wa_Dims[0]=2*m*n+4*n+12*m*m+12*m;
  capi_wa_intent |= F2PY_INTENT_INOUT;
  capi_wa_tmp = array_from_pyobj(PyArray_DOUBLE,wa_Dims,wa_Rank,capi_wa_intent,wa_capi);
  if (capi_wa_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 10th argument `wa' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    wa = (double *)(capi_wa_tmp->data);

  /* Processing variable iwa */
  iwa_Dims[0]=3 * n;
  capi_iwa_intent |= F2PY_INTENT_INOUT;
  capi_iwa_tmp = array_from_pyobj(PyArray_INT,iwa_Dims,iwa_Rank,capi_iwa_intent,iwa_capi);
  if (capi_iwa_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 11st argument `iwa' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    iwa = (int *)(capi_iwa_tmp->data);

  /* Processing variable nbd */
  nbd_Dims[0]=n;
  capi_nbd_intent |= F2PY_INTENT_IN;
  capi_nbd_tmp = array_from_pyobj(PyArray_INT,nbd_Dims,nbd_Rank,capi_nbd_intent,nbd_capi);
  if (capi_nbd_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 5th argument `nbd' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    nbd = (int *)(capi_nbd_tmp->data);

  /* Processing variable g */
  g_Dims[0]=n;
  capi_g_intent |= F2PY_INTENT_INOUT;
  capi_g_tmp = array_from_pyobj(PyArray_DOUBLE,g_Dims,g_Rank,capi_g_intent,g_capi);
  if (capi_g_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 7th argument `g' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    g = (double *)(capi_g_tmp->data);

  /* Processing variable l */
  l_Dims[0]=n;
  capi_l_intent |= F2PY_INTENT_IN;
  capi_l_tmp = array_from_pyobj(PyArray_DOUBLE,l_Dims,l_Rank,capi_l_intent,l_capi);
  if (capi_l_tmp == NULL) {
    if (!PyErr_Occurred())
      PyErr_SetString(_lbfgsb_error,"failed in converting 3rd argument `l' of _lbfgsb.setulb to C/Fortran array" );
  } else {
    l = (double *)(capi_l_tmp->data);

/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(&n,&m,x,l,u,nbd,&f,g,&factr,&pgtol,wa,iwa,task,&iprint,csave,lsave,isave,dsave,slen(task),slen(csave));
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
    if (f2py_success) {
/*pyobjfrom*/
  f2py_success = try_pyarr_from_double(f_capi,&f);
  if (f2py_success) {
  f2py_success = try_pyarr_from_string(task_capi,task);
  if (f2py_success) {
  f2py_success = try_pyarr_from_string(csave_capi,csave);
  if (f2py_success) {
/*end of pyobjfrom*/
    CFUNCSMESS("Building return value.\n");
    capi_buildvalue = Py_BuildValue("");
/*closepyobjfrom*/
  } /*if (f2py_success) of csave pyobjfrom*/
  } /*if (f2py_success) of task pyobjfrom*/
  } /*if (f2py_success) of f pyobjfrom*/
/*end of closepyobjfrom*/
    } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  if((PyObject *)capi_l_tmp!=l_capi) {
    Py_XDECREF(capi_l_tmp); }
  }  /*if (capi_l_tmp == NULL) ... else of l*/
  /* End of cleaning variable l */
  if((PyObject *)capi_g_tmp!=g_capi) {
    Py_XDECREF(capi_g_tmp); }
  }  /*if (capi_g_tmp == NULL) ... else of g*/
  /* End of cleaning variable g */
  if((PyObject *)capi_nbd_tmp!=nbd_capi) {
    Py_XDECREF(capi_nbd_tmp); }
  }  /*if (capi_nbd_tmp == NULL) ... else of nbd*/
  /* End of cleaning variable nbd */
  if((PyObject *)capi_iwa_tmp!=iwa_capi) {
    Py_XDECREF(capi_iwa_tmp); }
  }  /*if (capi_iwa_tmp == NULL) ... else of iwa*/
  /* End of cleaning variable iwa */
  if((PyObject *)capi_wa_tmp!=wa_capi) {
    Py_XDECREF(capi_wa_tmp); }
  }  /*if (capi_wa_tmp == NULL) ... else of wa*/
  /* End of cleaning variable wa */
  if((PyObject *)capi_u_tmp!=u_capi) {
    Py_XDECREF(capi_u_tmp); }
  }  /*if (capi_u_tmp == NULL) ... else of u*/
  /* End of cleaning variable u */
  } /*CHECKSCALAR(len(x)>=n)*/
  } /*if (f2py_success) of n*/
  /* End of cleaning variable n */
  } /*if (f2py_success) of pgtol*/
  /* End of cleaning variable pgtol */
  if((PyObject *)capi_x_tmp!=x_capi) {
    Py_XDECREF(capi_x_tmp); }
  }  /*if (capi_x_tmp == NULL) ... else of x*/
  /* End of cleaning variable x */
  if((PyObject *)capi_isave_tmp!=isave_capi) {
    Py_XDECREF(capi_isave_tmp); }
  }  /*if (capi_isave_tmp == NULL) ... else of isave*/
  /* End of cleaning variable isave */
  } /*if (f2py_success) of m*/
  /* End of cleaning variable m */
  } /*if (f2py_success) of iprint*/
  /* End of cleaning variable iprint */
  } /*if (f2py_success) of f*/
  /* End of cleaning variable f */
  if((PyObject *)capi_dsave_tmp!=dsave_capi) {
    Py_XDECREF(capi_dsave_tmp); }
  }  /*if (capi_dsave_tmp == NULL) ... else of dsave*/
  /* End of cleaning variable dsave */
    STRINGFREE(task);
  }  /*if (f2py_success) of task*/
  /* End of cleaning variable task */
  } /*if (f2py_success) of factr*/
  /* End of cleaning variable factr */
    STRINGFREE(csave);
  }  /*if (f2py_success) of csave*/
  /* End of cleaning variable csave */
  if((PyObject *)capi_lsave_tmp!=lsave_capi) {
    Py_XDECREF(capi_lsave_tmp); }
  }  /*if (capi_lsave_tmp == NULL) ... else of lsave*/
  /* End of cleaning variable lsave */
/*end of cleanupfrompyobj*/
  if (capi_buildvalue == NULL) {
/*routdebugfailure*/
  } else {
/*routdebugleave*/
  }
  CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
  return capi_buildvalue;
}
/******************************* end of setulb *******************************/
/*eof body*/

/******************* See f2py2e/f90mod_rules.py: buildhooks *******************/
/*need_f90modhooks*/

/************** See f2py2e/rules.py: module_rules['modulebody'] **************/

/******************* See f2py2e/common_rules.py: buildhooks *******************/

/*need_commonhooks*/

/**************************** See f2py2e/rules.py ****************************/

static FortranDataDef f2py_routine_defs[] = {
  {"setulb",-1,{{-1}},0,(char *)F_FUNC(setulb,SETULB),(f2py_init_func)f2py_rout__lbfgsb_setulb,doc_f2py_rout__lbfgsb_setulb},

/*eof routine_defs*/
  {NULL}
};

static PyMethodDef f2py_module_methods[] = {

  {NULL,NULL}
};

#if PY_VERSION_HEX >= 0x03000000
static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "_lbfgsb",
  NULL,
  -1,
  f2py_module_methods,
  NULL,
  NULL,
  NULL,
  NULL
};
#endif

#if PY_VERSION_HEX >= 0x03000000
#define RETVAL m
PyObject *PyInit__lbfgsb(void) {
#else
#define RETVAL
PyMODINIT_FUNC init_lbfgsb(void) {
#endif
  int i;
  PyObject *m,*d, *s;
#if PY_VERSION_HEX >= 0x03000000
  m = _lbfgsb_module = PyModule_Create(&moduledef);
#else
  m = _lbfgsb_module = Py_InitModule("_lbfgsb", f2py_module_methods);
#endif
  Py_TYPE(&PyFortran_Type) = &PyType_Type;
  import_array();
  if (PyErr_Occurred())
    {PyErr_SetString(PyExc_ImportError, "can't initialize module _lbfgsb (failed to import numpy)"); return RETVAL;}
  d = PyModule_GetDict(m);
  s = PyString_FromString("$Revision: $");
  PyDict_SetItemString(d, "__version__", s);
#if PY_VERSION_HEX >= 0x03000000
  s = PyUnicode_FromString(
#else
  s = PyString_FromString(
#endif
    "This module '_lbfgsb' is auto-generated with f2py (version:2).\nFunctions:\n"
"  setulb(m,x,l,u,nbd,f,g,factr,pgtol,wa,iwa,task,iprint,csave,lsave,isave,dsave,n=len(x))\n"
".");
  PyDict_SetItemString(d, "__doc__", s);
  _lbfgsb_error = PyErr_NewException ("_lbfgsb.error", NULL, NULL);
  Py_DECREF(s);
  for(i=0;f2py_routine_defs[i].name!=NULL;i++)
    PyDict_SetItemString(d, f2py_routine_defs[i].name,PyFortranObject_NewAsAttr(&f2py_routine_defs[i]));

/*eof initf2pywraphooks*/
/*eof initf90modhooks*/

/*eof initcommonhooks*/


#ifdef F2PY_REPORT_ATEXIT
  if (! PyErr_Occurred())
    on_exit(f2py_report_on_exit,(void*)"_lbfgsb");
#endif

  return RETVAL;
}
#ifdef __cplusplus
}
#endif
