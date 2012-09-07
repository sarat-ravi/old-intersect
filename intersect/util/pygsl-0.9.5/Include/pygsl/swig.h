#ifndef _PYGSL_SWIG_H_
#define _PYGSL_SWIG_H_ 1

SWIGINTERN PyObject*
SWIG_Python_AppendOutput(PyObject* result, PyObject* obj) {
#if !defined(SWIG_PYTHON_OUTPUT_TUPLE)
	if (!result) {
		result = obj;
	} else if (result == Py_None) {
		Py_DECREF(result);
		result = obj;
	} else {
		if (!PyList_Check(result)) {
			PyObject *o2 = result;
			result = PyList_New(1);
			PyList_SetItem(result, 0, o2);
		}
		PyList_Append(result,obj);
		Py_DECREF(obj);
	}
	return result;
#else
	PyObject*   o2;
	PyObject*   o3;
	if (!result) {
		result = obj;
	} else if (result == Py_None) {
		Py_DECREF(result);
		result = obj;
	} else {
		if (!PyTuple_Check(result)) {
			o2 = result;
			result = PyTuple_New(1);
			PyTuple_SET_ITEM(result, 0, o2);
		}
		o3 = PyTuple_New(1);
		PyTuple_SET_ITEM(o3, 0, obj);
		o2 = result;
		result = PySequence_Concat(o2, o3);
		Py_DECREF(o2);
		Py_DECREF(o3);
	}
	return result;
#endif
}

#endif /* _PYGSL_SWIG_H_ */
/*
 *
 */
