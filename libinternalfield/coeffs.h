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
extern std::vector<std::string> modelNames;

/* pointers to the memory where coefficients are stored (to be removed)*/
extern unsigned char _binary_ness1975_bin_start;
extern unsigned char _binary_o6_bin_start;
extern unsigned char _binary_sha_bin_start;
extern unsigned char _binary_gsfc15evs_bin_start;
extern unsigned char _binary_vip4_bin_start;
extern unsigned char _binary_p11a_bin_start;
extern unsigned char _binary_o4_bin_start;
extern unsigned char _binary_gsfc15ev_bin_start;
extern unsigned char _binary_gsfc13ev_bin_start;
extern unsigned char _binary_isaac_bin_start;
extern unsigned char _binary_jrm09_bin_start;
extern unsigned char _binary_jpl15evs_bin_start;
extern unsigned char _binary_jpl15ev_bin_start;
extern unsigned char _binary_vit4_bin_start;
extern unsigned char _binary_langlais2019_bin_start;
extern unsigned char _binary_v117ev_bin_start;
extern unsigned char _binary_jrm33_bin_start;
extern unsigned char _binary_u17ev_bin_start;
extern unsigned char _binary_vipal_bin_start;


/* model coefficient arrays */
extern coeffStruct& _model_coeff_ness1975();
extern coeffStruct& _model_coeff_o6();
extern coeffStruct& _model_coeff_sha();
extern coeffStruct& _model_coeff_gsfc15evs();
extern coeffStruct& _model_coeff_vip4();
extern coeffStruct& _model_coeff_p11a();
extern coeffStruct& _model_coeff_o4();
extern coeffStruct& _model_coeff_gsfc15ev();
extern coeffStruct& _model_coeff_gsfc13ev();
extern coeffStruct& _model_coeff_isaac();
extern coeffStruct& _model_coeff_jrm09();
extern coeffStruct& _model_coeff_jpl15evs();
extern coeffStruct& _model_coeff_jpl15ev();
extern coeffStruct& _model_coeff_vit4();
extern coeffStruct& _model_coeff_langlais2019();
extern coeffStruct& _model_coeff_v117ev();
extern coeffStruct& _model_coeff_jrm33();
extern coeffStruct& _model_coeff_u17ev();
extern coeffStruct& _model_coeff_vipal();

/* map model names to the structure containing the coefficients */
extern std::map<std::string,coeffStructFunc> coeffMap;

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


/* map the model names to their pointers (to be removed) */
extern std::map<std::string,unsigned char*> modelMap;

/* fucntions to return the pointer to a model given a string/const char (these will all be removed too)*/

/***********************************************************************
 * NAME : getModelCoeffPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to the memory address
 *			where the model coefficients are stored.
 *		
 * INPUTS : 
 *		std::string Model	Model name (use lower case!).
 *
 * RETURNS :
 *		unsigned char *ptr	Pointer to model data.
 *
 **********************************************************************/
unsigned char* getModelCoeffPointer(std::string Model);

/***********************************************************************
 * NAME : getModelCoeffPointer(Model)
 *
 * DESCRIPTION : Function to return a pointer to the memory address
 *			where the model coefficients are stored.
 *		
 * INPUTS : 
 *		const char *Model	Model name (use lower case!).
 *
 * RETURNS :
 *		unsigned char *ptr	Pointer to model data.
 *
 **********************************************************************/
unsigned char* getModelCoeffPointer(const char *Model);


