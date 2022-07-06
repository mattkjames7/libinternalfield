#ifndef __COEFFS_H__
#define __COEFFS_H__
#include <vector>
#include <string>
#include <map>


/* structure for storing the coefficients in memory (replaces binary stuff) */
typedef struct coeffStruct {
    const int len;    
    const int nmax;
    const int ndef;
    const double rscale;
    const int *n;
    const int *m;
    const double *g;
    const double *h;
} coeffStruct;

typedef coeffStruct& (*coeffStructFunc)();


#endif
/* list of model names */
std::vector<std::string> getModelNames();

/* model coefficient arrays */
extern coeffStruct& _model_coeff_gsfc15evs();
extern coeffStruct& _model_coeff_vip4();
extern coeffStruct& _model_coeff_v117ev();
extern coeffStruct& _model_coeff_gsfc15ev();
extern coeffStruct& _model_coeff_gsfc13ev();
extern coeffStruct& _model_coeff_vipal();
extern coeffStruct& _model_coeff_jpl15evs();
extern coeffStruct& _model_coeff_u17ev();
extern coeffStruct& _model_coeff_jrm09();
extern coeffStruct& _model_coeff_o6();
extern coeffStruct& _model_coeff_o4();
extern coeffStruct& _model_coeff_sha();
extern coeffStruct& _model_coeff_p11a();
extern coeffStruct& _model_coeff_jrm33();
extern coeffStruct& _model_coeff_vit4();
extern coeffStruct& _model_coeff_isaac();
extern coeffStruct& _model_coeff_jpl15ev();
extern coeffStruct& _model_coeff_langlais2019();
extern coeffStruct& _model_coeff_nmoh();
extern coeffStruct& _model_coeff_gsfco8full();
extern coeffStruct& _model_coeff_gsfco8();
extern coeffStruct& _model_coeff_ness1975();
extern coeffStruct& _model_coeff_gsfcq3full();
extern coeffStruct& _model_coeff_gsfcq3();
extern coeffStruct& _model_coeff_umoh();

/* map model names to the structure containing the coefficients */
std::map<std::string,coeffStructFunc> getCoeffMap();

/***********************************************************************
 * NAME : getModelCoeffStruct(Model)
 *
 * DESCRIPTION : Function to return a structure containing model 
        coefficients.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		coeffStructFunc	cstr    Model coefficient function.
 *
 **********************************************************************/
coeffStructFunc getModelCoeffStruct(std::string Model);

/***********************************************************************
 * NAME : getModelCoeffStruct(Model)
 *
 * DESCRIPTION : Function to return a structure containing model 
        coefficients.
 *		
 * INPUTS : 
 *		const char *Model	Model name (use lower case!).
 *
 * RETURNS :
 *		coeffStructFunc	cstr    Model coefficient function.
 *
 **********************************************************************/
coeffStructFunc getModelCoeffStruct(const char *Model);


