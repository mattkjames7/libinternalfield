#include "savemodels.h"

std::string getModelsHeaderIncludes() {
    std::string out = R"(    
#ifndef __MODELS_H__
#define __MODELS_H__
#include <vector>
#include <string>
#include <map>
#include "internal.h"
#include "coeffs.h"
#include "listmapkeys.h"
)";

    return out + "\n\n";
}

std::string getModelsHeaderExterns(ModelFileTuples models) {

    std::ostringstream out;
    for (auto &model :  models) {
        out << "extern Internal& ";
        out << std::get<0>(model);
        out << "();\n";
    }
    out << "\n\n";

    return out.str();
}

std::string getModelsHeaderMiscPrototypes() {

    std::string out = R"(

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

extern "C" {
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

)";
    return out;
}

std::string getModelsHeaderPrototypes(ModelFileTuples models) {

    std::ostringstream out;

    out << R"(
/* functions to directly call each model for a single Cartesian vector 
    (these will be used for tracing) */

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
)";

    for (auto &model : models) {
        out << "\tvoid ";
        out << std::get<0>(model);
        out << "Field(double x, double y, double z,\n";
        out << "\t\t\t\tdouble *bx, double *by, double *bz);\n";
    }

    out << "}\n";
    return out.str();
}

void saveModelsHeader(ModelFileTuples models,std::filesystem::path srcPath) {

    std::filesystem::path filePath = srcPath;
    filePath /= "models.h";
    std::cout << "Saving variable model header:" << std::endl;
    std::cout << "\t" << filePath << std::endl;

    std::ofstream file(filePath);
    file << getModelsHeaderIncludes();
    file << getModelsHeaderExterns(models);
    file << getModelsHeaderMiscPrototypes();
    file << getModelsHeaderPrototypes(models);
    file << "#endif\n";
    file.close();
}


std::string modelDefinition(ModelFileTuple model) {
    
    std::ostringstream out;
    out << "Internal& ";
    out << std::get<0>(model);
    out << "() {\n";
    out << "\tstatic Internal model(\"";
    out << std::get<0>(model);
    out << "\");\n";
    out << "\treturn model;\n";
    out << "}\n\n";

    return out.str();
}

std::string getModelsCCDefinitions(ModelFileTuples models) {

    std::ostringstream out;
    out << "#include \"models.h\"\n\n";

    for (auto &model : models) {
        out << modelDefinition(model);
    }
    return out.str();
}

std::string modelPtrMapping(ModelFileTuple model) {
    std::ostringstream out;
    std::string name = std::get<0>(model);
    out << "\t\t\t" << "{\"" << name << "\"," << name << "},\n";
    return out.str();
}

std::string getModelsCCModelPtrMap(ModelFileTuples models) {

    std::ostringstream out;
    out << "/* map the model names to their model object pointers */\n";
    out << "std::map<std::string,InternalFunc> getModelPtrMap() {\n";
    out << "\tstatic std::map<std::string,InternalFunc> modelPtrMap = {\n";
    for (auto &model : models) {
        out << modelPtrMapping(model);
    }
    out << "\t};\n";
    out << "\treturn modelPtrMap;\n";
    out << "}\n\n";
    return out.str();
}

std::string getModelsCCMisc0() {
    std::string out = R"(

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

)";
    return out;
}

std::string modelFieldPtrMapping(ModelFileTuple model) {
    std::ostringstream out;
    std::string name = std::get<0>(model);
    out << "\t\t\t" << "{\"" << name << "\",&" << name << "Field},\n";
    return out.str();
}


std::string getModelsCCModelFieldPtrMap(ModelFileTuples models) {

    std::ostringstream out;
    out << "/* map of strings to direct field model function pointers */\n";
    out << "std::map<std::string,modelFieldPtr> getModelFieldPtrMap() {\n";
    out << "\tstatic std::map<std::string,modelFieldPtr> modelFieldPtrMap = {\n";
    for (auto &model : models) {
        out << modelFieldPtrMapping(model);
    }
    out << "\t};\n";
    out << "\treturn modelFieldPtrMap;\n";
    out << "}\n\n";
    return out.str();
}

std::string getModelsCCMisc1() {
    std::string out = R"(

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

    )";
    return out;
}


std::string fieldFunctionDef(ModelFileTuple model) {
    std::ostringstream out;
    std::string name = std::get<0>(model);
    out << "void " << name << "Field(double x, double y, double z,\n";
    out << "\t\t\t\tdouble *bx, double *by, double *bz) {\n";
    out << "\tInternal model = " << name << "();\n";
    out << "\tmodel.FieldCart(x,y,z,bx,by,bz);\n";
    out << "}\n\n";
    return out.str();
}

std::string getModelsCCFieldFunctions(ModelFileTuples models) {

    std::ostringstream out;

    out << R"(

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
)";
    out << "\n";

    for (auto &model : models) {
        out << fieldFunctionDef(model);
    }
    return out.str();
}

void saveModelsCC(ModelFileTuples models,std::filesystem::path srcPath) {

    std::filesystem::path filePath = srcPath;
    filePath /= "models.cc";
    std::cout << "Saving model code:" << std::endl;
    std::cout << "\t" << filePath << std::endl;

    std::ofstream file(filePath);

    file << getModelsCCDefinitions(models);
    file << getModelsCCModelPtrMap(models);
    file << getModelsCCMisc0();
    file << getModelsCCModelFieldPtrMap(models);
    file << getModelsCCMisc1();
    file << getModelsCCFieldFunctions(models);
    
    file.close();
}


void saveModels(std::filesystem::path dataPath,std::filesystem::path srcPath) {

    std::filesystem::path coeffPath = dataPath;
    coeffPath /= "coeffs";

    ModelFileTuples models = listModels(coeffPath);
    

    saveModelsHeader(models,srcPath);
    saveModelsCC(models,srcPath);

}