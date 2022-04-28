#include "models.h"

/* model definitions */
//Internal ness1975(&_binary_ness1975_bin_start);
//Internal ness1975(&_model_coeff_ness1975);
Internal ness1975("ness1975");
//Internal o6(&_binary_o6_bin_start);
//Internal o6(&_model_coeff_o6);
Internal o6("o6");
//Internal sha(&_binary_sha_bin_start);
//Internal sha(&_model_coeff_sha);
Internal sha("sha");
//Internal gsfc15evs(&_binary_gsfc15evs_bin_start);
//Internal gsfc15evs(&_model_coeff_gsfc15evs);
Internal gsfc15evs("gsfc15evs");
//Internal vip4(&_binary_vip4_bin_start);
//Internal vip4(&_model_coeff_vip4);
Internal vip4("vip4");
//Internal p11a(&_binary_p11a_bin_start);
//Internal p11a(&_model_coeff_p11a);
Internal p11a("p11a");
//Internal o4(&_binary_o4_bin_start);
//Internal o4(&_model_coeff_o4);
Internal o4("o4");
//Internal gsfc15ev(&_binary_gsfc15ev_bin_start);
//Internal gsfc15ev(&_model_coeff_gsfc15ev);
Internal gsfc15ev("gsfc15ev");
//Internal gsfc13ev(&_binary_gsfc13ev_bin_start);
//Internal gsfc13ev(&_model_coeff_gsfc13ev);
Internal gsfc13ev("gsfc13ev");
//Internal isaac(&_binary_isaac_bin_start);
//Internal isaac(&_model_coeff_isaac);
Internal isaac("isaac");
//Internal jrm09(&_binary_jrm09_bin_start);
//Internal jrm09(&_model_coeff_jrm09);
Internal jrm09("jrm09");
//Internal jpl15evs(&_binary_jpl15evs_bin_start);
//Internal jpl15evs(&_model_coeff_jpl15evs);
Internal jpl15evs("jpl15evs");
//Internal jpl15ev(&_binary_jpl15ev_bin_start);
//Internal jpl15ev(&_model_coeff_jpl15ev);
Internal jpl15ev("jpl15ev");
//Internal vit4(&_binary_vit4_bin_start);
//Internal vit4(&_model_coeff_vit4);
Internal vit4("vit4");
//Internal langlais2019(&_binary_langlais2019_bin_start);
//Internal langlais2019(&_model_coeff_langlais2019);
Internal langlais2019("langlais2019");
//Internal v117ev(&_binary_v117ev_bin_start);
//Internal v117ev(&_model_coeff_v117ev);
Internal v117ev("v117ev");
//Internal jrm33(&_binary_jrm33_bin_start);
//Internal jrm33(&_model_coeff_jrm33);
Internal jrm33("jrm33");
//Internal u17ev(&_binary_u17ev_bin_start);
//Internal u17ev(&_model_coeff_u17ev);
Internal u17ev("u17ev");
//Internal vipal(&_binary_vipal_bin_start);
//Internal vipal(&_model_coeff_vipal);
Internal vipal("vipal");

/* map the model names to their model object pointers */
std::map<std::string,Internal*> modelPtrMap = {	{"ness1975",&ness1975},
										{"o6",&o6},
										{"sha",&sha},
										{"gsfc15evs",&gsfc15evs},
										{"vip4",&vip4},
										{"p11a",&p11a},
										{"o4",&o4},
										{"gsfc15ev",&gsfc15ev},
										{"gsfc13ev",&gsfc13ev},
										{"isaac",&isaac},
										{"jrm09",&jrm09},
										{"jpl15evs",&jpl15evs},
										{"jpl15ev",&jpl15ev},
										{"vit4",&vit4},
										{"langlais2019",&langlais2019},
										{"v117ev",&v117ev},
										{"jrm33",&jrm33},
										{"u17ev",&u17ev},
										{"vipal",&vipal}
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
std::map<std::string,modelFieldPtr> modelFieldPtrMap = {	{"ness1975",&ness1975Field},
													{"o6",&o6Field},
													{"sha",&shaField},
													{"gsfc15evs",&gsfc15evsField},
													{"vip4",&vip4Field},
													{"p11a",&p11aField},
													{"o4",&o4Field},
													{"gsfc15ev",&gsfc15evField},
													{"gsfc13ev",&gsfc13evField},
													{"isaac",&isaacField},
													{"jrm09",&jrm09Field},
													{"jpl15evs",&jpl15evsField},
													{"jpl15ev",&jpl15evField},
													{"vit4",&vit4Field},
													{"langlais2019",&langlais2019Field},
													{"v117ev",&v117evField},
													{"jrm33",&jrm33Field},
													{"u17ev",&u17evField},
													{"vipal",&vipalField}
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
void ness1975Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	ness1975.FieldCart(x,y,z,Bx,By,Bz);
}

void o6Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	o6.FieldCart(x,y,z,Bx,By,Bz);
}

void shaField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	sha.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfc15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	gsfc15evs.FieldCart(x,y,z,Bx,By,Bz);
}

void vip4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	vip4.FieldCart(x,y,z,Bx,By,Bz);
}

void p11aField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	p11a.FieldCart(x,y,z,Bx,By,Bz);
}

void o4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	o4.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfc15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	gsfc15ev.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfc13evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	gsfc13ev.FieldCart(x,y,z,Bx,By,Bz);
}

void isaacField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	isaac.FieldCart(x,y,z,Bx,By,Bz);
}

void jrm09Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jrm09.FieldCart(x,y,z,Bx,By,Bz);
}

void jpl15evsField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jpl15evs.FieldCart(x,y,z,Bx,By,Bz);
}

void jpl15evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jpl15ev.FieldCart(x,y,z,Bx,By,Bz);
}

void vit4Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	vit4.FieldCart(x,y,z,Bx,By,Bz);
}

void langlais2019Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	langlais2019.FieldCart(x,y,z,Bx,By,Bz);
}

void v117evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	v117ev.FieldCart(x,y,z,Bx,By,Bz);
}

void jrm33Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	jrm33.FieldCart(x,y,z,Bx,By,Bz);
}

void u17evField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	u17ev.FieldCart(x,y,z,Bx,By,Bz);
}

void vipalField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	vipal.FieldCart(x,y,z,Bx,By,Bz);
}

