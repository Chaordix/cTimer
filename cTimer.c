/* 
 * File:   cTimer.c
 * Author: Russ Porosky
 *
 * Created on May 3 2012
 */

#include "Python.h"

#if PY_MAJOR_VERSION >= 3
	#define MOD_ERROR_VAL NULL
	#define MOD_SUCCESS_VAL(val) val
	#define MOD_INIT(name) PyMODINIT_FUNC PyInit_##name(void)
    #define MOD_DEF(ob, name, doc, methods) \
        static struct PyModuleDef moduledef = { \
            PyModuleDef_HEAD_INIT, name, doc, -1, methods, }; \
        ob = PyModule_Create(&moduledef);
#else
	#define MOD_ERROR_VAL
	#define MOD_SUCCESS_VAL(val)
	#define MOD_INIT(name) PyMODINIT_FUNC init##name(void)
    #define MOD_DEF(ob, name, doc, methods) \
        ob = Py_InitModule3(name, methods, doc);
#endif


#include <time.h>

#ifdef __APPLE__ // OSX-only
#include "osxGetTime.h"
#endif

static double *times = NULL;
static int num_elements = 0;
static int num_allocated = 0;

int addToArray(double item) {
	if (num_elements >= num_allocated) {
		if (num_allocated == 0) {
			num_allocated = 20;
		} else {
			num_allocated = num_allocated + 20;
		}
		void *_tmp = realloc(times, (num_allocated * sizeof(double)));
		if (!_tmp) {
			fprintf(stderr, "ERROR: Couldn't realloc memory!\n");
			return(-1);
		}
		times = (double*)_tmp;
	}
	times[num_elements] = (double)item;
	num_elements++;
	return num_elements - 1;
}

double convertTsToDouble(struct timespec thetime) {
	return ((double)thetime.tv_nsec / (double)1000000000) + (double)thetime.tv_sec;
}

double diff(double start, double end) {
	double tmp = end - start;
	if (tmp < 0) {
		tmp = tmp * -1;
	}
	return (double)tmp;
}

struct timespec gettime(void) {
	struct timespec temp;
#ifdef CLOCK_MONOTONIC_RAW
	clock_gettime(CLOCK_MONOTONIC_RAW, &temp);
#elif CLOCK_MONOTONIC
	clock_gettime(CLOCK_MONOTONIC, &temp);
#elif CLOCK_REALTIME
	clock_gettime(CLOCK_REALTIME, &temp);
#endif
	return temp;
}

static PyObject *
timer_start(PyObject *self, PyObject *args)
{
	return Py_BuildValue("i", addToArray(convertTsToDouble(gettime())));
};

static PyObject *
timer_checkpoint(PyObject *self, PyObject *args)
{
	return Py_BuildValue("i", addToArray(convertTsToDouble(gettime())));
};

static PyObject *
timer_stop(PyObject *self, PyObject *args)
{
	return Py_BuildValue("i", addToArray(convertTsToDouble(gettime())));
};

static PyObject *
timer_diff(PyObject *self, PyObject *args)
{
	int time1;
	int time2;
	if (!PyArg_ParseTuple(args, "ii", &time1, &time2)) {
		return NULL;
	}
	if (time1 >= num_elements || time2 >= num_elements || time1 < 0 || time2 < 0) {
		PyErr_SetString(PyExc_IndexError, "Invalid timer ID.");
		return NULL;
	}
	return Py_BuildValue("d", (double)diff(times[time1], times[time2]));
};

static PyObject *
timer_get(PyObject *self, PyObject *args)
{
	return Py_BuildValue("d", diff(times[0], convertTsToDouble(gettime())));
};

static PyMethodDef TimerMethods[] = {
	{"get",  timer_get, METH_NOARGS, "Get a relative timestamp as a float."},
	{"start",  timer_start, METH_NOARGS, "Get timer ID for a start point."},
	{"checkpoint",  timer_checkpoint, METH_NOARGS, "Get timer ID for a checkpoint."},
	{"stop",  timer_stop, METH_NOARGS, "Get timer ID for a stop point."},
	{"diff",  timer_diff, METH_VARARGS, "Get the difference in seconds between two checkpoint IDs as a double."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};


MOD_INIT(cTimer)
{
	addToArray(convertTsToDouble(gettime()));
	PyObject *m;

    MOD_DEF(m, "cTimer", "A high precision timer.",
            TimerMethods)
            
    if (m == NULL)
        return MOD_ERROR_VAL;
    
    return MOD_SUCCESS_VAL(m);
	//(void) Py_InitModule3("cTimer", TimerMethods, "A high precision timer.");
}
