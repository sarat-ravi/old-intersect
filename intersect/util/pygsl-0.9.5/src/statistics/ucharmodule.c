/**
 * author: Jochen K"upper
 * created: Jan 2002
 * file: pygsl/src/statistics/longmodule.c
 * $Id: ucharmodule.c,v 1.5 2004/03/24 08:40:45 schnizer Exp $
 *
 *"
 */


#include <Python.h>
#include <pygsl/error_helpers.h>
#include <pygsl/block_helpers.h>
#include <gsl/gsl_statistics.h>


/* include real functions for different data-types */

#define STATMOD_APPEND_PY_TYPE(X) X ## Int
#define STATMOD_APPEND_PYC_TYPE(X) X ## UBYTE
#define STATMOD_FUNC_EXT(X, Y) X ## _uchar ## Y
#define STATMOD_PY_AS_C PyInt_AsLong
#define STATMOD_C_TYPE unsigned char
#include "functions.c"






PyGSL_STATISTICS_INIT(uchar, "uchar")


/*
 * Local Variables:
 * mode: c
 * c-file-style: "Stroustrup"
 * End:
 */
