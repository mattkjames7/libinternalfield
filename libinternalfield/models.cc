#include "models.h"

/* model definitions */
Internal& gsfc15evs() {
	static Internal model("gsfc15evs");
	return model;
}

Internal& vip4() {
	static Internal model("vip4");
	return model;
}

Internal& v117ev() {
	static Internal model("v117ev");
	return model;
}

Internal& gsfc15ev() {
	static Internal model("gsfc15ev");
	return model;
}

Internal& gsfc13ev() {
	static Internal model("gsfc13ev");
	return model;
}

Internal& vipal() {
	static Internal model("vipal");
	return model;
}

Internal& jpl15evs() {
	static Internal model("jpl15evs");
	return model;
}

Internal& u17ev() {
	static Internal model("u17ev");
	return model;
}

Internal& jrm09() {
	static Internal model("jrm09");
	return model;
}

Internal& ness1975() {
	static Internal model("ness1975");
	return model;
}

Internal& o6() {
	static Internal model("o6");
	return model;
}

Internal& o4() {
	static Internal model("o4");
	return model;
}

Internal& gsfcq3() {
	static Internal model("gsfcq3");
	return model;
}

Internal& sha() {
	static Internal model("sha");
	return model;
}

Internal& p11a() {
	static Internal model("p11a");
	return model;
}

Internal& jrm33() {
	static Internal model("jrm33");
	return model;
}

Internal& langlais2019() {
	static Internal model("langlais2019");
	return model;
}

Internal& vit4() {
	static Internal model("vit4");
	return model;
}

Internal& isaac() {
	static Internal model("isaac");
	return model;
}

Internal& jpl15ev() {
	static Internal model("jpl15ev");
	return model;
}


/* map the model names to their model object pointers */
std::map<std::string,InternalFunc> getModelPtrMap() {
	static std::map<std::string,InternalFunc> modelPtrMap = {
										{"gsfc15evs",gsfc15evs},
										{"vip4",vip4},
										{"v117ev",v117ev},
										{"gsfc15ev",gsfc15ev},
										{"gsfc13ev",gsfc13ev},
										{"vipal",vipal},
										{"jpl15evs",jpl15evs},
										{"u17ev",u17ev},
										{"jrm09",jrm09},
										{"ness1975",ness1975},
										{"o6",o6},
										{"o4",o4},
										{"gsfcq3",gsfcq3},
										{"sha",sha},
										{"p11a",p11a},
										{"jrm33",jrm33},
										{"langlais2019",langlais2019},
										{"vit4",vit4},
										{"isaac",isaac},
										{"jpl15ev",jpl15ev}
	};
	return modelPtrMap;
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
 *		InternalFunc *ptr		Function pointer to model object.
 *
 **********************************************************************/
InternalFunc getModelObjPointer(std::string Model) {
    std::map<std::string,InternalFunc> modelPtrMap = getModelPtrMap();
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
 *		InternalFunc *ptr		Function pointer to model object.
 *
 **********************************************************************/
InternalFunc getModelObjPointer(const char *Model) {
    std::map<std::string,InternalFunc> modelPtrMap = getModelPtrMap();
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
	return listMapKeys(getModelPtrMap());
}

/* map of strings to direct field model function pointers */
std::map<std::string,modelFieldPtr> getModelFieldPtrMap() {
	static std::map<std::string,modelFieldPtr> modelFieldPtrMap = {
													{"gsfc15evs",&gsfc15evsField},
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
													{"gsfcq3",&gsfcq3Field},
													{"sha",&shaField},
													{"p11a",&p11aField},
													{"jrm33",&jrm33Field},
													{"langlais2019",&langlais2019Field},
													{"vit4",&vit4Field},
													{"isaac",&isaacField},
													{"jpl15ev",&jpl15evField}
	};
	return modelFieldPtrMap;
}

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
    std::map<std::string,modelFieldPtr> modelFieldPtrMap = getModelFieldPtrMap();
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
    std::map<std::string,modelFieldPtr> modelFieldPtrMap = getModelFieldPtrMap();
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
	Internal model = gsfc15evs();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void vip4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = vip4();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void v117evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = v117ev();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfc15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gsfc15ev();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfc13evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gsfc13ev();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void vipalField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = vipal();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void jpl15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = jpl15evs();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void u17evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = u17ev();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void jrm09Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = jrm09();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void ness1975Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = ness1975();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void o6Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = o6();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void o4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = o4();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfcq3Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gsfcq3();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void shaField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = sha();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void p11aField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = p11a();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void jrm33Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = jrm33();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void langlais2019Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = langlais2019();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void vit4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = vit4();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void isaacField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = isaac();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void jpl15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = jpl15ev();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

