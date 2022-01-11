#ifndef __LIBINTERNAL_H__
#define __LIBINTERNAL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "models.h"
#include "internalmodel.h"

using namespace std;

/* we want to initialize the model objects witht heir parameters */
extern InternalModel internalModel;

extern "C" {
	/* these wrappers can be used to get the magnetic field vectors */

	void InternalField(int n, double *p0, double *p1, double *p2,
						double *B0, double *B1, double *B2);
	void InternalFieldDeg(int n, double *p0, double *p1, double *p2,
						int MaxDeg, double *B0, double *B1, double *B2);
	void SetInternalCFG(const char *Model, bool CartIn, bool CartOut);

	void GetInternalCFG(char *Model, bool *CartIn, bool *CartOut);

	
}
#endif
