#define PyGSL_NUMERIC
#define PyGSL_NUMARRAY
#include "numeric_numarray.h"
#include <gsl/gsl_errno.h>
#include <pygsl/general_helpers.h>

static int
cp_numeric_ptrs(void)
{
     return GSL_SUCCESS;
}

static int
cp_numarray_ptrs(void)
{
     return GSL_SUCCESS;
}


void
initnumx(void)
{
     init_pygsl();
     cp_numeric_ptrs();
     cp_numarray_ptrs();
}
