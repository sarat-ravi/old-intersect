#include <Python.h>

void
init_test(void)
{    
   PyObject *m;
   m = Py_InitModule("_test", NULL);
}
