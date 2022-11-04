#include "libinternal.h"

/* we want to initialize the model objects witht heir parameters */

InternalModel getInternalModel() {
	static InternalModel internalModel;
	return internalModel;
}

/***********************************************************************
 * NAME : InternalField(n,p0,p1,p2,B0,B1,B2)
 *
 * DESCRIPTION : Call the model field function. Coordinates depend 
 * 		on the model  configuration
 *		
 * INPUTS : 
 * 		int		n			Number of array elements
 *		double	*p0			x or r coordinate in planetary radii.
 *		double	*p1			y coordinate in planetary radii or theta 
 * 							in radians.
 *		double	*p2			z coordinate in planetary radii or phi
 * 							in radians.
 *
 * OUTPUTS :
 *		double	*B0			x or r component of the field (nT).
 *		double	*B1			y or theta component of the field (nT).
 *		double	*B2			z or phi component of the field (nT).
 * 
 **********************************************************************/
void InternalField(int n, double *p0, double *p1, double *p2,
					double *B0, double *B1, double *B2) {
	
	InternalModel internalModel = getInternalModel();
	internalModel.Field(n,p0,p1,p2,B0,B1,B2);
				
}

/***********************************************************************
 * NAME : InternalFieldDeg(n,p0,p1,p2,MaxDeg,B0,B1,B2)
 *
 * DESCRIPTION : Call the model field function. Coordinates depend 
 * 		on the model  configuration
 *		
 * INPUTS : 
 * 		int		n			Number of array elements
 *		double	*p0			x or r coordinate in planetary radii.
 *		double	*p1			y coordinate in planetary radii or theta 
 * 							in radians.
 *		double	*p2			z coordinate in planetary radii or phi
 * 							in radians.
 * 		int 	MaxDeg		Maximum model degree to use.
 *
 * OUTPUTS :
 *		double	*B0			x or r component of the field (nT).
 *		double	*B1			y or theta component of the field (nT).
 *		double	*B2			z or phi component of the field (nT).
 * 
 **********************************************************************/
void InternalFieldDeg(int n, double *p0, double *p1, double *p2,
					int MaxDeg, double *B0, double *B1, double *B2) {
	
	InternalModel internalModel = getInternalModel();
	internalModel.Field(n,p0,p1,p2,MaxDeg,B0,B1,B2);
				
}

/***********************************************************************
 * NAME : SetInternalCFG(Model,CartIn,CartOut,MaxDeg)
 *
 * DESCRIPTION : Configure the current model.
 *		
 * INPUTS : 
 * 		const char *Model		Model name.
 * 		bool CartIn				Set to True for Cartesian input
 * 								coordinates or false for polar.
 * 		bool CartOut			As above, but for the output.
 * 		int  MaxDeg				Maximum degree used by model
 * 
 **********************************************************************/
void SetInternalCFG(const char *Model, bool CartIn, bool CartOut, int MaxDeg) {
	
	InternalModel internalModel = getInternalModel();
	internalModel.SetCartIn(CartIn);
	internalModel.SetCartOut(CartOut);
	internalModel.SetModel(Model);
	internalModel.SetDegree(MaxDeg);
}

/***********************************************************************
 * NAME : GetInternalCFG(Model,CartIn,CartOut,MaxDeg)
 *
 * DESCRIPTION : Return the current model configuration.
 *		
 * OUTPUTS : 
 * 		char *Model				Model name.
 * 		bool CartIn				True for Cartesian input
 * 								coordinates or false for polar.
 * 		bool CartOut			As above, but for the output.
 * 		int  MaxDeg				Maximum degree used by model
 * 
 **********************************************************************/
void GetInternalCFG(char *Model, bool *CartIn, bool *CartOut, int *MaxDeg) {
	
	InternalModel internalModel = getInternalModel();
	CartIn[0] = internalModel.GetCartIn();
	CartOut[0] = internalModel.GetCartOut();
	internalModel.GetModel(Model);
	MaxDeg[0] = internalModel.GetDegree();
}

