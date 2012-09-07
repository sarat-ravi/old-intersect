/**
 * original author: Jochen K"upper
 * author: Pierre Schnizer
 * created: Jan 2002
 * modified: May 2009
 * file: pygsl/src/statistics/longmodule.c
 * $Id: charmodule.c,v 1.9 2009/05/11 08:53:03 schnizer Exp $
 *
 *
 *"
 */


#include <Python.h>
#include <pygsl/error_helpers.h>
#include <pygsl/block_helpers.h>
#include <gsl/gsl_statistics.h>


/* include real functions for different data-types */

#define STATMOD_APPEND_PY_TYPE(X) X ## Int

#if (defined PyGSL_NUMARRAY) || (defined PyGSL_NUMERIC)
#define STATMOD_APPEND_PYC_TYPE(X) X ## CHAR
#else /* PyGSL_NUMARRAY */ 
#define STATMOD_APPEND_PYC_TYPE(X) X ## BYTE
#endif /* PyGSL_NUMARRAY */

#define STATMOD_FUNC_EXT(X, Y) X ## _char ## Y
#define STATMOD_PY_AS_C PyInt_AsLong
#define STATMOD_C_TYPE char
#include "functions.c"




PyGSL_STATISTICS_INIT(char, "char")


/*
 * Local Variables:
 * mode: c
 * c-file-style: "python"
 * End:
 */
