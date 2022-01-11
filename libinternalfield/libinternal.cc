#include "libinternal.h"

/* we want to initialize the model objects witht heir parameters */

InternalModel internalModel;

void InternalField(int n, double *p0, double *p1, double *p2,
					double *B0, double *B1, double *B2) {

	internalModel.Field(n,p0,p1,p2,B0,B1,B2);
				
}

void InternalFieldDeg(int n, double *p0, double *p1, double *p2,
					int MaxDeg, double *B0, double *B1, double *B2) {

	internalModel.Field(n,p0,p1,p2,MaxDeg,B0,B1,B2);
				
}

void SetInternalCFG(const char *Model, bool CartIn, bool CartOut) {
	internalModel.SetCartIn(CartIn);
	internalModel.SetCartOut(CartOut);
	internalModel.SetModel(Model);
}

void GetInternalCFG(char *Model, bool *CartIn, bool *CartOut) {
	CartIn[0] = internalModel.GetCartIn();
	CartOut[0] = internalModel.GetCartOut();
	internalModel.GetModel(Model);
}

