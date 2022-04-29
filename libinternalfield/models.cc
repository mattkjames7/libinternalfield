#include "models.h"

/* model definitions */
Internal gsfc15evs("gsfc15evs");
Internal vip4("vip4");
Internal v117ev("v117ev");
Internal gsfc15ev("gsfc15ev");
Internal gsfc13ev("gsfc13ev");
Internal vipal("vipal");
Internal jpl15evs("jpl15evs");
Internal u17ev("u17ev");
Internal jrm09("jrm09");
Internal ness1975("ness1975");
Internal o6("o6");
Internal o4("o4");
Internal sha("sha");
Internal p11a("p11a");
Internal jrm33("jrm33");
Internal langlais2019("langlais2019");
Internal vit4("vit4");
Internal isaac("isaac");
Internal jpl15ev("jpl15ev");

/* map the model names to their model object pointers */
std::map<std::string,Internal*> modelPtrMap = {	{"gsfc15evs",&gsfc15evs},
										{"vip4",&vip4},
										{"v117ev",&v117ev},
										{"gsfc15ev",&gsfc15ev},
										{"gsfc13ev",&gsfc13ev},
										{"vipal",&vipal},
										{"jpl15evs",&jpl15evs},
										{"u17ev",&u17ev},
										{"jrm09",&jrm09},
										{"ness1975",&ness1975},
										{"o6",&o6},
										{"o4",&o4},
										{"sha",&sha},
										{"p11a",&p11a},
										{"jrm33",&jrm33},
										{"langlais2019",&langlais2019},
										{"vit4",&vit4},
										{"isaac",&isaac},
										{"jpl15ev",&jpl15ev}
};


/***********************************************************************
 * NAME : getModelObjPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a model object.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		Internal *ptr		Pointer to model object.
 *
 **********************************************************************/
Internal* getModelObjPointer(std::string Model) {
	return modelPtrMap[Model];
}

/***********************************************************************
 * NAME : getModelObjPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to a model object.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		Internal *ptr		Pointer to model object.
 *
 **********************************************************************/
Internal* getModelObjPointer(const char *Model) {
	return modelPtrMap[Model];
}

/***********************************************************************
 * NAME : listAvailableModels()
 *
 * DESCRIPTION : Function to return a list of model names available.
 *		
 * RETURNS :
 *		vector<string> Models	Model list.
 *
 **********************************************************************/
std::vector<std::string> listAvailableModels() {
	return listMapKeys(modelPtrMap);
}

/* map of strings to direct field model function pointers */
std::map<std::string,modelFieldPtr> modelFieldPtrMap = {	{"gsfc15evs",&gsfc15evsField},
													{"vip4",&vip4Field},
													{"v117ev",&v117evField},
													{"gsfc15ev",&gsfc15evField},
													{"gsfc13ev",&gsfc13evField},
													{"vipal",&vipalField},
													{"jpl15evs",&jpl15evsField},
													{"u17ev",&u17evField},
													{"jrm09",&jrm09Field},
													{"ness1975",&ness1975Field},
													{"o6",&o6Field},
													{"o4",&o4Field},
													{"sha",&shaField},
													{"p11a",&p11aField},
													{"jrm33",&jrm33Field},
													{"langlais2019",&langlais2019Field},
													{"vit4",&vit4Field},
													{"isaac",&isaacField},
													{"jpl15ev",&jpl15evField}
};


/* function to return pointer to model field function */

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
 *******************************************************************/
modelFieldPtr getModelFieldPtr(std::string Model) {
    return modelFieldPtrMap[Model];
}

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
modelFieldPtr getModelFieldPtr(const char *Model) {
    return modelFieldPtrMap[Model];
}

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
				double *Bx, double *By, double *Bz) {
	gsfc15evs.FieldCart(x,y,z,Bx,By,Bz);
}

void vip4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	vip4.FieldCart(x,y,z,Bx,By,Bz);
}

void v117evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	v117ev.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfc15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	gsfc15ev.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfc13evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	gsfc13ev.FieldCart(x,y,z,Bx,By,Bz);
}

void vipalField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	vipal.FieldCart(x,y,z,Bx,By,Bz);
}

void jpl15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jpl15evs.FieldCart(x,y,z,Bx,By,Bz);
}

void u17evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	u17ev.FieldCart(x,y,z,Bx,By,Bz);
}

void jrm09Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jrm09.FieldCart(x,y,z,Bx,By,Bz);
}

void ness1975Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	ness1975.FieldCart(x,y,z,Bx,By,Bz);
}

void o6Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	o6.FieldCart(x,y,z,Bx,By,Bz);
}

void o4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	o4.FieldCart(x,y,z,Bx,By,Bz);
}

void shaField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	sha.FieldCart(x,y,z,Bx,By,Bz);
}

void p11aField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	p11a.FieldCart(x,y,z,Bx,By,Bz);
}

void jrm33Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jrm33.FieldCart(x,y,z,Bx,By,Bz);
}

void langlais2019Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	langlais2019.FieldCart(x,y,z,Bx,By,Bz);
}

void vit4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	vit4.FieldCart(x,y,z,Bx,By,Bz);
}

void isaacField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	isaac.FieldCart(x,y,z,Bx,By,Bz);
}

void jpl15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jpl15ev.FieldCart(x,y,z,Bx,By,Bz);
}

