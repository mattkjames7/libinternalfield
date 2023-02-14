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
extern coeffStruct& _model_coeff_spv();
extern coeffStruct& _model_coeff_soi();
extern coeffStruct& _model_coeff_v2();
extern coeffStruct& _model_coeff_cassini3();
extern coeffStruct& _model_coeff_cassini5();
extern coeffStruct& _model_coeff_z3();
extern coeffStruct& _model_coeff_burton2009();
extern coeffStruct& _model_coeff_v1();
extern coeffStruct& _model_coeff_cassini11();
extern coeffStruct& _model_coeff_p1184();
extern coeffStruct& _model_coeff_p11as();
extern coeffStruct& _model_coeff_kivelson2002b();
extern coeffStruct& _model_coeff_kivelson2002a();
extern coeffStruct& _model_coeff_kivelson2002c();
extern coeffStruct& _model_coeff_weber2022dip();
extern coeffStruct& _model_coeff_weber2022quad();
extern coeffStruct& _model_coeff_mh2014();
extern coeffStruct& _model_coeff_cain2003();
extern coeffStruct& _model_coeff_langlais2019();
extern coeffStruct& _model_coeff_gao2021();
extern coeffStruct& _model_coeff_igrf1935();
extern coeffStruct& _model_coeff_igrf2005();
extern coeffStruct& _model_coeff_igrf2000();
extern coeffStruct& _model_coeff_igrf1950();
extern coeffStruct& _model_coeff_igrf1960();
extern coeffStruct& _model_coeff_igrf1985();
extern coeffStruct& _model_coeff_igrf1945();
extern coeffStruct& _model_coeff_igrf1965();
extern coeffStruct& _model_coeff_igrf1905();
extern coeffStruct& _model_coeff_igrf2010();
extern coeffStruct& _model_coeff_igrf2020();
extern coeffStruct& _model_coeff_igrf1910();
extern coeffStruct& _model_coeff_igrf1990();
extern coeffStruct& _model_coeff_igrf2015();
extern coeffStruct& _model_coeff_igrf1925();
extern coeffStruct& _model_coeff_igrf2025();
extern coeffStruct& _model_coeff_igrf1970();
extern coeffStruct& _model_coeff_igrf1930();
extern coeffStruct& _model_coeff_igrf1920();
extern coeffStruct& _model_coeff_igrf1955();
extern coeffStruct& _model_coeff_igrf1995();
extern coeffStruct& _model_coeff_igrf1900();
extern coeffStruct& _model_coeff_igrf1980();
extern coeffStruct& _model_coeff_igrf1940();
extern coeffStruct& _model_coeff_igrf1975();
extern coeffStruct& _model_coeff_igrf1915();
extern coeffStruct& _model_coeff_nmoh();
extern coeffStruct& _model_coeff_gsfco8full();
extern coeffStruct& _model_coeff_gsfco8();
extern coeffStruct& _model_coeff_thebault2018m3();
extern coeffStruct& _model_coeff_anderson2010qts04();
extern coeffStruct& _model_coeff_uno2009svd();
extern coeffStruct& _model_coeff_anderson2012();
extern coeffStruct& _model_coeff_thebault2018m1();
extern coeffStruct& _model_coeff_anderson2010dts04();
extern coeffStruct& _model_coeff_anderson2010q();
extern coeffStruct& _model_coeff_anderson2010d();
extern coeffStruct& _model_coeff_anderson2010qsha();
extern coeffStruct& _model_coeff_anderson2010dsha();
extern coeffStruct& _model_coeff_ness1975();
extern coeffStruct& _model_coeff_uno2009();
extern coeffStruct& _model_coeff_anderson2010r();
extern coeffStruct& _model_coeff_thebault2018m2();
extern coeffStruct& _model_coeff_ah5();
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


