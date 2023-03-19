#ifndef __COEFFS_H__
#define __COEFFS_H__
#include <vector>
#include <string>
#include <map>


/* structure for storing the coefficients in memory (replaces binary stuff) */
typedef struct coeffStruct {
    int len = 0;    
    int nmax = 0;
    int ndef = 0;
    double rscale = 0.0;
    std::vector<int> n;
    std::vector<int> m;
    std::vector<double> g;
    std::vector<double> h;
} coeffStruct;

typedef coeffStruct& (*coeffStructFunc)();


#endif
/* list of model names */
std::vector<std::string> getModelNames();

/* model coefficient arrays */
extern coeffStruct& _model_coeff_gsfc15evs();
extern unsigned char _binary_coeffs_jupiter_gsfc15evs_bin_start;
extern coeffStruct& _model_coeff_vip4();
extern unsigned char _binary_coeffs_jupiter_vip4_bin_start;
extern coeffStruct& _model_coeff_v117ev();
extern unsigned char _binary_coeffs_jupiter_v117ev_bin_start;
extern coeffStruct& _model_coeff_gsfc15ev();
extern unsigned char _binary_coeffs_jupiter_gsfc15ev_bin_start;
extern coeffStruct& _model_coeff_gsfc13ev();
extern unsigned char _binary_coeffs_jupiter_gsfc13ev_bin_start;
extern coeffStruct& _model_coeff_vipal();
extern unsigned char _binary_coeffs_jupiter_vipal_bin_start;
extern coeffStruct& _model_coeff_jpl15evs();
extern unsigned char _binary_coeffs_jupiter_jpl15evs_bin_start;
extern coeffStruct& _model_coeff_u17ev();
extern unsigned char _binary_coeffs_jupiter_u17ev_bin_start;
extern coeffStruct& _model_coeff_jrm09();
extern unsigned char _binary_coeffs_jupiter_jrm09_bin_start;
extern coeffStruct& _model_coeff_o6();
extern unsigned char _binary_coeffs_jupiter_o6_bin_start;
extern coeffStruct& _model_coeff_o4();
extern unsigned char _binary_coeffs_jupiter_o4_bin_start;
extern coeffStruct& _model_coeff_sha();
extern unsigned char _binary_coeffs_jupiter_sha_bin_start;
extern coeffStruct& _model_coeff_p11a();
extern unsigned char _binary_coeffs_jupiter_p11a_bin_start;
extern coeffStruct& _model_coeff_jrm33();
extern unsigned char _binary_coeffs_jupiter_jrm33_bin_start;
extern coeffStruct& _model_coeff_vit4();
extern unsigned char _binary_coeffs_jupiter_vit4_bin_start;
extern coeffStruct& _model_coeff_isaac();
extern unsigned char _binary_coeffs_jupiter_isaac_bin_start;
extern coeffStruct& _model_coeff_jpl15ev();
extern unsigned char _binary_coeffs_jupiter_jpl15ev_bin_start;
extern coeffStruct& _model_coeff_spv();
extern unsigned char _binary_coeffs_saturn_spv_bin_start;
extern coeffStruct& _model_coeff_soi();
extern unsigned char _binary_coeffs_saturn_soi_bin_start;
extern coeffStruct& _model_coeff_v2();
extern unsigned char _binary_coeffs_saturn_v2_bin_start;
extern coeffStruct& _model_coeff_cassini3();
extern unsigned char _binary_coeffs_saturn_cassini3_bin_start;
extern coeffStruct& _model_coeff_cassini5();
extern unsigned char _binary_coeffs_saturn_cassini5_bin_start;
extern coeffStruct& _model_coeff_z3();
extern unsigned char _binary_coeffs_saturn_z3_bin_start;
extern coeffStruct& _model_coeff_burton2009();
extern unsigned char _binary_coeffs_saturn_burton2009_bin_start;
extern coeffStruct& _model_coeff_v1();
extern unsigned char _binary_coeffs_saturn_v1_bin_start;
extern coeffStruct& _model_coeff_cassini11();
extern unsigned char _binary_coeffs_saturn_cassini11_bin_start;
extern coeffStruct& _model_coeff_p1184();
extern unsigned char _binary_coeffs_saturn_p1184_bin_start;
extern coeffStruct& _model_coeff_p11as();
extern unsigned char _binary_coeffs_saturn_p11as_bin_start;
extern coeffStruct& _model_coeff_kivelson2002b();
extern unsigned char _binary_coeffs_ganymede_kivelson2002b_bin_start;
extern coeffStruct& _model_coeff_kivelson2002a();
extern unsigned char _binary_coeffs_ganymede_kivelson2002a_bin_start;
extern coeffStruct& _model_coeff_kivelson2002c();
extern unsigned char _binary_coeffs_ganymede_kivelson2002c_bin_start;
extern coeffStruct& _model_coeff_weber2022dip();
extern unsigned char _binary_coeffs_ganymede_weber2022dip_bin_start;
extern coeffStruct& _model_coeff_weber2022quad();
extern unsigned char _binary_coeffs_ganymede_weber2022quad_bin_start;
extern coeffStruct& _model_coeff_mh2014();
extern unsigned char _binary_coeffs_mars_mh2014_bin_start;
extern coeffStruct& _model_coeff_cain2003();
extern unsigned char _binary_coeffs_mars_cain2003_bin_start;
extern coeffStruct& _model_coeff_langlais2019();
extern unsigned char _binary_coeffs_mars_langlais2019_bin_start;
extern coeffStruct& _model_coeff_gao2021();
extern unsigned char _binary_coeffs_mars_gao2021_bin_start;
extern coeffStruct& _model_coeff_igrf1935();
extern unsigned char _binary_coeffs_earth_igrf1935_bin_start;
extern coeffStruct& _model_coeff_igrf2005();
extern unsigned char _binary_coeffs_earth_igrf2005_bin_start;
extern coeffStruct& _model_coeff_igrf2000();
extern unsigned char _binary_coeffs_earth_igrf2000_bin_start;
extern coeffStruct& _model_coeff_igrf1950();
extern unsigned char _binary_coeffs_earth_igrf1950_bin_start;
extern coeffStruct& _model_coeff_igrf1960();
extern unsigned char _binary_coeffs_earth_igrf1960_bin_start;
extern coeffStruct& _model_coeff_igrf1985();
extern unsigned char _binary_coeffs_earth_igrf1985_bin_start;
extern coeffStruct& _model_coeff_igrf1945();
extern unsigned char _binary_coeffs_earth_igrf1945_bin_start;
extern coeffStruct& _model_coeff_igrf1965();
extern unsigned char _binary_coeffs_earth_igrf1965_bin_start;
extern coeffStruct& _model_coeff_igrf1905();
extern unsigned char _binary_coeffs_earth_igrf1905_bin_start;
extern coeffStruct& _model_coeff_igrf2010();
extern unsigned char _binary_coeffs_earth_igrf2010_bin_start;
extern coeffStruct& _model_coeff_igrf2020();
extern unsigned char _binary_coeffs_earth_igrf2020_bin_start;
extern coeffStruct& _model_coeff_igrf1910();
extern unsigned char _binary_coeffs_earth_igrf1910_bin_start;
extern coeffStruct& _model_coeff_igrf1990();
extern unsigned char _binary_coeffs_earth_igrf1990_bin_start;
extern coeffStruct& _model_coeff_igrf2015();
extern unsigned char _binary_coeffs_earth_igrf2015_bin_start;
extern coeffStruct& _model_coeff_igrf1925();
extern unsigned char _binary_coeffs_earth_igrf1925_bin_start;
extern coeffStruct& _model_coeff_igrf2025();
extern unsigned char _binary_coeffs_earth_igrf2025_bin_start;
extern coeffStruct& _model_coeff_igrf1970();
extern unsigned char _binary_coeffs_earth_igrf1970_bin_start;
extern coeffStruct& _model_coeff_igrf1930();
extern unsigned char _binary_coeffs_earth_igrf1930_bin_start;
extern coeffStruct& _model_coeff_igrf1920();
extern unsigned char _binary_coeffs_earth_igrf1920_bin_start;
extern coeffStruct& _model_coeff_igrf1955();
extern unsigned char _binary_coeffs_earth_igrf1955_bin_start;
extern coeffStruct& _model_coeff_igrf1995();
extern unsigned char _binary_coeffs_earth_igrf1995_bin_start;
extern coeffStruct& _model_coeff_igrf1900();
extern unsigned char _binary_coeffs_earth_igrf1900_bin_start;
extern coeffStruct& _model_coeff_igrf1980();
extern unsigned char _binary_coeffs_earth_igrf1980_bin_start;
extern coeffStruct& _model_coeff_igrf1940();
extern unsigned char _binary_coeffs_earth_igrf1940_bin_start;
extern coeffStruct& _model_coeff_igrf1975();
extern unsigned char _binary_coeffs_earth_igrf1975_bin_start;
extern coeffStruct& _model_coeff_igrf1915();
extern unsigned char _binary_coeffs_earth_igrf1915_bin_start;
extern coeffStruct& _model_coeff_nmoh();
extern unsigned char _binary_coeffs_neptune_nmoh_bin_start;
extern coeffStruct& _model_coeff_gsfco8full();
extern unsigned char _binary_coeffs_neptune_gsfco8full_bin_start;
extern coeffStruct& _model_coeff_gsfco8();
extern unsigned char _binary_coeffs_neptune_gsfco8_bin_start;
extern coeffStruct& _model_coeff_thebault2018m3();
extern unsigned char _binary_coeffs_mercury_thebault2018m3_bin_start;
extern coeffStruct& _model_coeff_anderson2010qts04();
extern unsigned char _binary_coeffs_mercury_anderson2010qts04_bin_start;
extern coeffStruct& _model_coeff_uno2009svd();
extern unsigned char _binary_coeffs_mercury_uno2009svd_bin_start;
extern coeffStruct& _model_coeff_anderson2012();
extern unsigned char _binary_coeffs_mercury_anderson2012_bin_start;
extern coeffStruct& _model_coeff_thebault2018m1();
extern unsigned char _binary_coeffs_mercury_thebault2018m1_bin_start;
extern coeffStruct& _model_coeff_anderson2010dts04();
extern unsigned char _binary_coeffs_mercury_anderson2010dts04_bin_start;
extern coeffStruct& _model_coeff_anderson2010q();
extern unsigned char _binary_coeffs_mercury_anderson2010q_bin_start;
extern coeffStruct& _model_coeff_anderson2010d();
extern unsigned char _binary_coeffs_mercury_anderson2010d_bin_start;
extern coeffStruct& _model_coeff_anderson2010qsha();
extern unsigned char _binary_coeffs_mercury_anderson2010qsha_bin_start;
extern coeffStruct& _model_coeff_anderson2010dsha();
extern unsigned char _binary_coeffs_mercury_anderson2010dsha_bin_start;
extern coeffStruct& _model_coeff_ness1975();
extern unsigned char _binary_coeffs_mercury_ness1975_bin_start;
extern coeffStruct& _model_coeff_uno2009();
extern unsigned char _binary_coeffs_mercury_uno2009_bin_start;
extern coeffStruct& _model_coeff_anderson2010r();
extern unsigned char _binary_coeffs_mercury_anderson2010r_bin_start;
extern coeffStruct& _model_coeff_thebault2018m2();
extern unsigned char _binary_coeffs_mercury_thebault2018m2_bin_start;
extern coeffStruct& _model_coeff_ah5();
extern unsigned char _binary_coeffs_uranus_ah5_bin_start;
extern coeffStruct& _model_coeff_gsfcq3full();
extern unsigned char _binary_coeffs_uranus_gsfcq3full_bin_start;
extern coeffStruct& _model_coeff_gsfcq3();
extern unsigned char _binary_coeffs_uranus_gsfcq3_bin_start;
extern coeffStruct& _model_coeff_umoh();
extern unsigned char _binary_coeffs_uranus_umoh_bin_start;
/* map of memory locations */
std::map<std::string,unsigned char*> getCoeffPtrMap();

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


