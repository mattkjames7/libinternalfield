#ifndef __MODELS_H__
#define __MODELS_H__
#include <vector>
#include <string>
#include <map>
#include "internal.h"
#include "coeffs.h"
#include "listmapkeys.h"
#endif

/* models! */
extern Internal& gsfc15evs();
extern Internal& vip4();
extern Internal& v117ev();
extern Internal& gsfc15ev();
extern Internal& gsfc13ev();
extern Internal& vipal();
extern Internal& jpl15evs();
extern Internal& u17ev();
extern Internal& jrm09();
extern Internal& o6();
extern Internal& o4();
extern Internal& sha();
extern Internal& p11a();
extern Internal& jrm33();
extern Internal& vit4();
extern Internal& isaac();
extern Internal& jpl15ev();
extern Internal& langlais2019();
extern Internal& nmoh();
extern Internal& gsfco8full();
extern Internal& gsfco8();
extern Internal& thebault2018m3();
extern Internal& anderson2010qts04();
extern Internal& uno2009svd();
extern Internal& anderson2012();
extern Internal& thebault2018m1();
extern Internal& anderson2010dts04();
extern Internal& anderson2010q();
extern Internal& anderson2010d();
extern Internal& anderson2010qsha();
extern Internal& anderson2010dsha();
extern Internal& ness1975();
extern Internal& uno2009();
extern Internal& anderson2010r();
extern Internal& thebault2018m2();
extern Internal& ah5();
extern Internal& gsfcq3full();
extern Internal& gsfcq3();
extern Internal& umoh();


/* map the model names to their model object pointers */
typedef Internal& (*InternalFunc)();
std::map<std::string,InternalFunc> getModelPtrMap();

/* functions to return the pointer to a model object given a string */

/***********************************************************************
 * NAME : getModelObjPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a model object.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		InternalFunc ptr		Function pointer to model object.
 *
 **********************************************************************/
InternalFunc getModelObjPointer(std::string Model);

/***********************************************************************
 * NAME : getModelObjPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a model object.
 *		
 * INPUTS : 
 *		const char *Model	Model name (use lower case!).
 *
 * RETURNS :
 *		InternalFunc ptr		Function pointer to model object.
 *
 **********************************************************************/
InternalFunc getModelObjPointer(const char *Model);

/* a function to return a list of the models available */
/***********************************************************************
 * NAME : listAvailableModels()
 *
 * DESCRIPTION : Function to return a list of model names available.
 *		
 * RETURNS :
 *		vector<string> Models	Model list.
 *
 **********************************************************************/
std::vector<std::string> listAvailableModels();

/* map of strings to direct field model function pointers */
typedef void (*modelFieldPtr)(double,double,double,double*,double*,double*);
std::map<std::string,modelFieldPtr> getModelFieldPtrMap();

/* functions to return pointer to model field function */

/***********************************************************************
 * NAME : getModelFieldPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a wrapper function
 * 			which will provide a single field vector at a single 
 * 			position.
 *		
 * INPUTS : 
 *		std::string Model		Model name (use lower case!).
 *
 * RETURNS :
 *		modelFieldPtr *ptr		Pointer to model wrapper.
 *
 **********************************************************************/
modelFieldPtr getModelFieldPtr(std::string Model);

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
void langlais2019Field(double x, double y, double z,
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
