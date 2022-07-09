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

Internal& o6() {
	static Internal model("o6");
	return model;
}

Internal& o4() {
	static Internal model("o4");
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

Internal& mh2014() {
	static Internal model("mh2014");
	return model;
}

Internal& cain2003() {
	static Internal model("cain2003");
	return model;
}

Internal& langlais2019() {
	static Internal model("langlais2019");
	return model;
}

Internal& gao2021() {
	static Internal model("gao2021");
	return model;
}

Internal& nmoh() {
	static Internal model("nmoh");
	return model;
}

Internal& gsfco8full() {
	static Internal model("gsfco8full");
	return model;
}

Internal& gsfco8() {
	static Internal model("gsfco8");
	return model;
}

Internal& thebault2018m3() {
	static Internal model("thebault2018m3");
	return model;
}

Internal& anderson2010qts04() {
	static Internal model("anderson2010qts04");
	return model;
}

Internal& uno2009svd() {
	static Internal model("uno2009svd");
	return model;
}

Internal& anderson2012() {
	static Internal model("anderson2012");
	return model;
}

Internal& thebault2018m1() {
	static Internal model("thebault2018m1");
	return model;
}

Internal& anderson2010dts04() {
	static Internal model("anderson2010dts04");
	return model;
}

Internal& anderson2010q() {
	static Internal model("anderson2010q");
	return model;
}

Internal& anderson2010d() {
	static Internal model("anderson2010d");
	return model;
}

Internal& anderson2010qsha() {
	static Internal model("anderson2010qsha");
	return model;
}

Internal& anderson2010dsha() {
	static Internal model("anderson2010dsha");
	return model;
}

Internal& ness1975() {
	static Internal model("ness1975");
	return model;
}

Internal& uno2009() {
	static Internal model("uno2009");
	return model;
}

Internal& anderson2010r() {
	static Internal model("anderson2010r");
	return model;
}

Internal& thebault2018m2() {
	static Internal model("thebault2018m2");
	return model;
}

Internal& ah5() {
	static Internal model("ah5");
	return model;
}

Internal& gsfcq3full() {
	static Internal model("gsfcq3full");
	return model;
}

Internal& gsfcq3() {
	static Internal model("gsfcq3");
	return model;
}

Internal& umoh() {
	static Internal model("umoh");
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
										{"o6",o6},
										{"o4",o4},
										{"sha",sha},
										{"p11a",p11a},
										{"jrm33",jrm33},
										{"vit4",vit4},
										{"isaac",isaac},
										{"jpl15ev",jpl15ev},
										{"mh2014",mh2014},
										{"cain2003",cain2003},
										{"langlais2019",langlais2019},
										{"gao2021",gao2021},
										{"nmoh",nmoh},
										{"gsfco8full",gsfco8full},
										{"gsfco8",gsfco8},
										{"thebault2018m3",thebault2018m3},
										{"anderson2010qts04",anderson2010qts04},
										{"uno2009svd",uno2009svd},
										{"anderson2012",anderson2012},
										{"thebault2018m1",thebault2018m1},
										{"anderson2010dts04",anderson2010dts04},
										{"anderson2010q",anderson2010q},
										{"anderson2010d",anderson2010d},
										{"anderson2010qsha",anderson2010qsha},
										{"anderson2010dsha",anderson2010dsha},
										{"ness1975",ness1975},
										{"uno2009",uno2009},
										{"anderson2010r",anderson2010r},
										{"thebault2018m2",thebault2018m2},
										{"ah5",ah5},
										{"gsfcq3full",gsfcq3full},
										{"gsfcq3",gsfcq3},
										{"umoh",umoh}
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
													{"o6",&o6Field},
													{"o4",&o4Field},
													{"sha",&shaField},
													{"p11a",&p11aField},
													{"jrm33",&jrm33Field},
													{"vit4",&vit4Field},
													{"isaac",&isaacField},
													{"jpl15ev",&jpl15evField},
													{"mh2014",&mh2014Field},
													{"cain2003",&cain2003Field},
													{"langlais2019",&langlais2019Field},
													{"gao2021",&gao2021Field},
													{"nmoh",&nmohField},
													{"gsfco8full",&gsfco8fullField},
													{"gsfco8",&gsfco8Field},
													{"thebault2018m3",&thebault2018m3Field},
													{"anderson2010qts04",&anderson2010qts04Field},
													{"uno2009svd",&uno2009svdField},
													{"anderson2012",&anderson2012Field},
													{"thebault2018m1",&thebault2018m1Field},
													{"anderson2010dts04",&anderson2010dts04Field},
													{"anderson2010q",&anderson2010qField},
													{"anderson2010d",&anderson2010dField},
													{"anderson2010qsha",&anderson2010qshaField},
													{"anderson2010dsha",&anderson2010dshaField},
													{"ness1975",&ness1975Field},
													{"uno2009",&uno2009Field},
													{"anderson2010r",&anderson2010rField},
													{"thebault2018m2",&thebault2018m2Field},
													{"ah5",&ah5Field},
													{"gsfcq3full",&gsfcq3fullField},
													{"gsfcq3",&gsfcq3Field},
													{"umoh",&umohField}
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

void mh2014Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = mh2014();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void cain2003Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = cain2003();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void langlais2019Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = langlais2019();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gao2021Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gao2021();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void nmohField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = nmoh();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfco8fullField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gsfco8full();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfco8Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gsfco8();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void thebault2018m3Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = thebault2018m3();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2010qts04Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2010qts04();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void uno2009svdField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = uno2009svd();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2012Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2012();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void thebault2018m1Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = thebault2018m1();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2010dts04Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2010dts04();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2010qField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2010q();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2010dField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2010d();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2010qshaField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2010qsha();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2010dshaField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2010dsha();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void ness1975Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = ness1975();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void uno2009Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = uno2009();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void anderson2010rField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = anderson2010r();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void thebault2018m2Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = thebault2018m2();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void ah5Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = ah5();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfcq3fullField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gsfcq3full();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void gsfcq3Field(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = gsfcq3();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

void umohField(double x, double y, double z,
				double *Bx, double *By, double *Bz) {
	Internal model = umoh();
	model.FieldCart(x,y,z,Bx,By,Bz);
}

