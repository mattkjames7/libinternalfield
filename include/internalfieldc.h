#ifndef __LIBINTERNALFIELD_H__
#define __LIBINTERNALFIELD_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#define INTERNALFIELD_VERSION_MAJOR 1
#define INTERNALFIELD_VERSION_MINOR 1
#define INTERNALFIELD_VERSION_PATCH 0


/***********************************************************************
 * NAME : getModelFieldPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a wrapper function
 * 			which will provide a single field vector at a single 
 * 			position.
 *		
 * INPUTS : 
 *		const char *Model		Model name (use lower case!).
 *
 * RETURNS :
 *		modelFieldPtr *ptr		Pointer to model wrapper.
 *
 **********************************************************************/
modelFieldPtr getModelFieldPtr(const char *Model);

/* functions to directly call each model for a single Cartesian vector (this will be used for tracing) */

/***********************************************************************
 * NAME : XXXXXField(x,y,z,Bx,By,Bz)
 *
 * DESCRIPTION : Model wrapper functions which can be passed to the 
 * 			tracing code. Replace XXXXXX with the name of the model...
 *		
 * INPUTS : 
 *		double	x			x coordinate in planetary radii.
 *		double	y			y coordinate in planetary radii.
 *		double	z			z coordinate in planetary radii.
 *
 * OUTPUTS :
 *		double	*Bx			x component of the field (nT).
 *		double	*By			y component of the field (nT).
 *		double	*Bz			z component of the field (nT).
 * 
 **********************************************************************/
void gsfc15evsField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void vip4Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void v117evField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void gsfc15evField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void gsfc13evField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void vipalField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void jpl15evsField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void u17evField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void jrm09Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void o6Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void o4Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void shaField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void p11aField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void jrm33Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void vit4Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void isaacField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void jpl15evField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void spvField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void soiField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void v2Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void cassini3Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void cassini5Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void z3Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void burton2009Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void v1Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void p1184Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void p11asField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void mh2014Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void cain2003Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void langlais2019Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void gao2021Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1935Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf2005Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf2000Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1950Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1960Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1985Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1945Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1965Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1905Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf2010Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf2020Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1910Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1990Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf2015Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1925Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf2025Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1970Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1930Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1920Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1955Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1995Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1900Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1980Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1940Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1975Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void igrf1915Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void nmohField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void gsfco8fullField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void gsfco8Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void thebault2018m3Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2010qts04Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void uno2009svdField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2012Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void thebault2018m1Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2010dts04Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2010qField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2010dField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2010qshaField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2010dshaField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void ness1975Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void uno2009Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void anderson2010rField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void thebault2018m2Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void ah5Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void gsfcq3fullField(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void gsfcq3Field(double x, double y, double z,
			double *Bx, double *By, double *Bz);
void umohField(double x, double y, double z,
			double *Bx, double *By, double *Bz);




	/* these wrappers can be used to get the magnetic field vectors */

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
						double *B0, double *B1, double *B2);

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
						int MaxDeg, double *B0, double *B1, double *B2);

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
void SetInternalCFG(const char *Model, bool CartIn, bool CartOut, int MaxDeg);

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
void GetInternalCFG(char *Model, bool *CartIn, bool *CartOut, int *MaxDeg);

	

#endif