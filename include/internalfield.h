#ifndef __LIBINTERNALFIELD_H__
#define __LIBINTERNALFIELD_H__
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef __cplusplus
#include <vector>
#include <map>
#include <string>
#else 
#include <string.h>
#endif



#define INTERNALFIELD_VERSION_MAJOR 1
#define INTERNALFIELD_VERSION_MINOR 2
#define INTERNALFIELD_VERSION_PATCH 0

/* this is used in both C and C++*/
typedef void (*modelFieldPtr)(double,double,double,double*,double*,double*);

#ifdef __cplusplus
extern "C" {
#endif
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
	void spvField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void soiField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void v2Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void cassini3Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void cassini5Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void z3Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void burton2009Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void v1Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void cassini11Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void p1184Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void p11asField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void kivelson2002bField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void kivelson2002aField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void kivelson2002cField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void weber2022dipField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void weber2022quadField(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void mh2014Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void cain2003Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void langlais2019Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void gao2021Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1935Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf2005Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf2000Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1950Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1960Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1985Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1945Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1965Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1905Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf2010Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf2020Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1910Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1990Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf2015Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1925Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf2025Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1970Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1930Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1920Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1955Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1995Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1900Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1980Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1940Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1975Field(double x, double y, double z,
				double *Bx, double *By, double *Bz);
	void igrf1915Field(double x, double y, double z,
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
	/* these wrappers can be used to get the magnetic field vectors */

	/***********************************************************************
	 * NAME : InternalField(n,p0,p1,p2,B0,B1,B2)
	 *
	 * DESCRIPTION : Call the model field function. Coordinates depend 
	 * 		on the model  configuration
	 *		
	 * INPUTS : 
	 * 		int		n			Number of array elements
	 *		double	*p0			x or r coordinate in planetary radii.
	 *		double	*p1			y coordinate in planetary radii or theta 
	 * 							in radians.
	 *		double	*p2			z coordinate in planetary radii or phi
	 * 							in radians.
	 *
	 * OUTPUTS :
	 *		double	*B0			x or r component of the field (nT).
	 *		double	*B1			y or theta component of the field (nT).
	 *		double	*B2			z or phi component of the field (nT).
	 * 
	 **********************************************************************/
	void InternalField(int n, double *p0, double *p1, double *p2,
						double *B0, double *B1, double *B2);

	/***********************************************************************
	 * NAME : InternalFieldDeg(n,p0,p1,p2,MaxDeg,B0,B1,B2)
	 *
	 * DESCRIPTION : Call the model field function. Coordinates depend 
	 * 		on the model  configuration
	 *		
	 * INPUTS : 
	 * 		int		n			Number of array elements
	 *		double	*p0			x or r coordinate in planetary radii.
	 *		double	*p1			y coordinate in planetary radii or theta 
	 * 							in radians.
	 *		double	*p2			z coordinate in planetary radii or phi
	 * 							in radians.
	 * 		int 	MaxDeg		Maximum model degree to use.
	 *
	 * OUTPUTS :
	 *		double	*B0			x or r component of the field (nT).
	 *		double	*B1			y or theta component of the field (nT).
	 *		double	*B2			z or phi component of the field (nT).
	 * 
	 **********************************************************************/
	void InternalFieldDeg(int n, double *p0, double *p1, double *p2,
						int MaxDeg, double *B0, double *B1, double *B2);

	/***********************************************************************
	 * NAME : SetInternalCFG(Model,CartIn,CartOut,MaxDeg)
	 *
	 * DESCRIPTION : Configure the current model.
	 *		
	 * INPUTS : 
	 * 		const char *Model		Model name.
	 * 		bool CartIn				Set to True for Cartesian input
	 * 								coordinates or false for polar.
	 * 		bool CartOut			As above, but for the output.
	 * 		int  MaxDeg				Maximum degree used by model
	 * 
	 **********************************************************************/
	void SetInternalCFG(const char *Model, bool CartIn, bool CartOut, int MaxDeg);

	/***********************************************************************
	 * NAME : GetInternalCFG(Model,CartIn,CartOut,MaxDeg)
	 *
	 * DESCRIPTION : Return the current model configuration.
	 *		
	 * OUTPUTS : 
	 * 		char *Model				Model name.
	 * 		bool CartIn				True for Cartesian input
	 * 								coordinates or false for polar.
	 * 		bool CartOut			As above, but for the output.
	 * 		int  MaxDeg				Maximum degree used by model
	 * 
	 **********************************************************************/
	void GetInternalCFG(char *Model, bool *CartIn, bool *CartOut, int *MaxDeg);

	
#ifdef __cplusplus
}


/* structure for storing the coefficients in memory (replaces binary stuff) */
typedef struct coeffStruct {
    const int len;    
    const int nmax;
    const int ndef;
    const double rscale;
    std::vector<int> n;
    std::vector<int> m;
    std::vector<double> g;
    std::vector<double> h;
} coeffStruct;

typedef coeffStruct& (*coeffStructFunc)();


/* list of model names */
std::vector<std::string> getModelNames();

/* model coefficient arrays */
extern coeffStruct& _model_coeff_gsfc15evs();
extern unsigned char *_binary_coeffs_jupiter_gsfc15evs_bin_start;
extern coeffStruct& _model_coeff_vip4();
extern unsigned char *_binary_coeffs_jupiter_vip4_bin_start;
extern coeffStruct& _model_coeff_v117ev();
extern unsigned char *_binary_coeffs_jupiter_v117ev_bin_start;
extern coeffStruct& _model_coeff_gsfc15ev();
extern unsigned char *_binary_coeffs_jupiter_gsfc15ev_bin_start;
extern coeffStruct& _model_coeff_gsfc13ev();
extern unsigned char *_binary_coeffs_jupiter_gsfc13ev_bin_start;
extern coeffStruct& _model_coeff_vipal();
extern unsigned char *_binary_coeffs_jupiter_vipal_bin_start;
extern coeffStruct& _model_coeff_jpl15evs();
extern unsigned char *_binary_coeffs_jupiter_jpl15evs_bin_start;
extern coeffStruct& _model_coeff_u17ev();
extern unsigned char *_binary_coeffs_jupiter_u17ev_bin_start;
extern coeffStruct& _model_coeff_jrm09();
extern unsigned char *_binary_coeffs_jupiter_jrm09_bin_start;
extern coeffStruct& _model_coeff_o6();
extern unsigned char *_binary_coeffs_jupiter_o6_bin_start;
extern coeffStruct& _model_coeff_o4();
extern unsigned char *_binary_coeffs_jupiter_o4_bin_start;
extern coeffStruct& _model_coeff_sha();
extern unsigned char *_binary_coeffs_jupiter_sha_bin_start;
extern coeffStruct& _model_coeff_p11a();
extern unsigned char *_binary_coeffs_jupiter_p11a_bin_start;
extern coeffStruct& _model_coeff_jrm33();
extern unsigned char *_binary_coeffs_jupiter_jrm33_bin_start;
extern coeffStruct& _model_coeff_vit4();
extern unsigned char *_binary_coeffs_jupiter_vit4_bin_start;
extern coeffStruct& _model_coeff_isaac();
extern unsigned char *_binary_coeffs_jupiter_isaac_bin_start;
extern coeffStruct& _model_coeff_jpl15ev();
extern unsigned char *_binary_coeffs_jupiter_jpl15ev_bin_start;
extern coeffStruct& _model_coeff_spv();
extern unsigned char *_binary_coeffs_saturn_spv_bin_start;
extern coeffStruct& _model_coeff_soi();
extern unsigned char *_binary_coeffs_saturn_soi_bin_start;
extern coeffStruct& _model_coeff_v2();
extern unsigned char *_binary_coeffs_saturn_v2_bin_start;
extern coeffStruct& _model_coeff_cassini3();
extern unsigned char *_binary_coeffs_saturn_cassini3_bin_start;
extern coeffStruct& _model_coeff_cassini5();
extern unsigned char *_binary_coeffs_saturn_cassini5_bin_start;
extern coeffStruct& _model_coeff_z3();
extern unsigned char *_binary_coeffs_saturn_z3_bin_start;
extern coeffStruct& _model_coeff_burton2009();
extern unsigned char *_binary_coeffs_saturn_burton2009_bin_start;
extern coeffStruct& _model_coeff_v1();
extern unsigned char *_binary_coeffs_saturn_v1_bin_start;
extern coeffStruct& _model_coeff_cassini11();
extern unsigned char *_binary_coeffs_saturn_cassini11_bin_start;
extern coeffStruct& _model_coeff_p1184();
extern unsigned char *_binary_coeffs_saturn_p1184_bin_start;
extern coeffStruct& _model_coeff_p11as();
extern unsigned char *_binary_coeffs_saturn_p11as_bin_start;
extern coeffStruct& _model_coeff_kivelson2002b();
extern unsigned char *_binary_coeffs_ganymede_kivelson2002b_bin_start;
extern coeffStruct& _model_coeff_kivelson2002a();
extern unsigned char *_binary_coeffs_ganymede_kivelson2002a_bin_start;
extern coeffStruct& _model_coeff_kivelson2002c();
extern unsigned char *_binary_coeffs_ganymede_kivelson2002c_bin_start;
extern coeffStruct& _model_coeff_weber2022dip();
extern unsigned char *_binary_coeffs_ganymede_weber2022dip_bin_start;
extern coeffStruct& _model_coeff_weber2022quad();
extern unsigned char *_binary_coeffs_ganymede_weber2022quad_bin_start;
extern coeffStruct& _model_coeff_mh2014();
extern unsigned char *_binary_coeffs_mars_mh2014_bin_start;
extern coeffStruct& _model_coeff_cain2003();
extern unsigned char *_binary_coeffs_mars_cain2003_bin_start;
extern coeffStruct& _model_coeff_langlais2019();
extern unsigned char *_binary_coeffs_mars_langlais2019_bin_start;
extern coeffStruct& _model_coeff_gao2021();
extern unsigned char *_binary_coeffs_mars_gao2021_bin_start;
extern coeffStruct& _model_coeff_igrf1935();
extern unsigned char *_binary_coeffs_earth_igrf1935_bin_start;
extern coeffStruct& _model_coeff_igrf2005();
extern unsigned char *_binary_coeffs_earth_igrf2005_bin_start;
extern coeffStruct& _model_coeff_igrf2000();
extern unsigned char *_binary_coeffs_earth_igrf2000_bin_start;
extern coeffStruct& _model_coeff_igrf1950();
extern unsigned char *_binary_coeffs_earth_igrf1950_bin_start;
extern coeffStruct& _model_coeff_igrf1960();
extern unsigned char *_binary_coeffs_earth_igrf1960_bin_start;
extern coeffStruct& _model_coeff_igrf1985();
extern unsigned char *_binary_coeffs_earth_igrf1985_bin_start;
extern coeffStruct& _model_coeff_igrf1945();
extern unsigned char *_binary_coeffs_earth_igrf1945_bin_start;
extern coeffStruct& _model_coeff_igrf1965();
extern unsigned char *_binary_coeffs_earth_igrf1965_bin_start;
extern coeffStruct& _model_coeff_igrf1905();
extern unsigned char *_binary_coeffs_earth_igrf1905_bin_start;
extern coeffStruct& _model_coeff_igrf2010();
extern unsigned char *_binary_coeffs_earth_igrf2010_bin_start;
extern coeffStruct& _model_coeff_igrf2020();
extern unsigned char *_binary_coeffs_earth_igrf2020_bin_start;
extern coeffStruct& _model_coeff_igrf1910();
extern unsigned char *_binary_coeffs_earth_igrf1910_bin_start;
extern coeffStruct& _model_coeff_igrf1990();
extern unsigned char *_binary_coeffs_earth_igrf1990_bin_start;
extern coeffStruct& _model_coeff_igrf2015();
extern unsigned char *_binary_coeffs_earth_igrf2015_bin_start;
extern coeffStruct& _model_coeff_igrf1925();
extern unsigned char *_binary_coeffs_earth_igrf1925_bin_start;
extern coeffStruct& _model_coeff_igrf2025();
extern unsigned char *_binary_coeffs_earth_igrf2025_bin_start;
extern coeffStruct& _model_coeff_igrf1970();
extern unsigned char *_binary_coeffs_earth_igrf1970_bin_start;
extern coeffStruct& _model_coeff_igrf1930();
extern unsigned char *_binary_coeffs_earth_igrf1930_bin_start;
extern coeffStruct& _model_coeff_igrf1920();
extern unsigned char *_binary_coeffs_earth_igrf1920_bin_start;
extern coeffStruct& _model_coeff_igrf1955();
extern unsigned char *_binary_coeffs_earth_igrf1955_bin_start;
extern coeffStruct& _model_coeff_igrf1995();
extern unsigned char *_binary_coeffs_earth_igrf1995_bin_start;
extern coeffStruct& _model_coeff_igrf1900();
extern unsigned char *_binary_coeffs_earth_igrf1900_bin_start;
extern coeffStruct& _model_coeff_igrf1980();
extern unsigned char *_binary_coeffs_earth_igrf1980_bin_start;
extern coeffStruct& _model_coeff_igrf1940();
extern unsigned char *_binary_coeffs_earth_igrf1940_bin_start;
extern coeffStruct& _model_coeff_igrf1975();
extern unsigned char *_binary_coeffs_earth_igrf1975_bin_start;
extern coeffStruct& _model_coeff_igrf1915();
extern unsigned char *_binary_coeffs_earth_igrf1915_bin_start;
extern coeffStruct& _model_coeff_nmoh();
extern unsigned char *_binary_coeffs_neptune_nmoh_bin_start;
extern coeffStruct& _model_coeff_gsfco8full();
extern unsigned char *_binary_coeffs_neptune_gsfco8full_bin_start;
extern coeffStruct& _model_coeff_gsfco8();
extern unsigned char *_binary_coeffs_neptune_gsfco8_bin_start;
extern coeffStruct& _model_coeff_thebault2018m3();
extern unsigned char *_binary_coeffs_mercury_thebault2018m3_bin_start;
extern coeffStruct& _model_coeff_anderson2010qts04();
extern unsigned char *_binary_coeffs_mercury_anderson2010qts04_bin_start;
extern coeffStruct& _model_coeff_uno2009svd();
extern unsigned char *_binary_coeffs_mercury_uno2009svd_bin_start;
extern coeffStruct& _model_coeff_anderson2012();
extern unsigned char *_binary_coeffs_mercury_anderson2012_bin_start;
extern coeffStruct& _model_coeff_thebault2018m1();
extern unsigned char *_binary_coeffs_mercury_thebault2018m1_bin_start;
extern coeffStruct& _model_coeff_anderson2010dts04();
extern unsigned char *_binary_coeffs_mercury_anderson2010dts04_bin_start;
extern coeffStruct& _model_coeff_anderson2010q();
extern unsigned char *_binary_coeffs_mercury_anderson2010q_bin_start;
extern coeffStruct& _model_coeff_anderson2010d();
extern unsigned char *_binary_coeffs_mercury_anderson2010d_bin_start;
extern coeffStruct& _model_coeff_anderson2010qsha();
extern unsigned char *_binary_coeffs_mercury_anderson2010qsha_bin_start;
extern coeffStruct& _model_coeff_anderson2010dsha();
extern unsigned char *_binary_coeffs_mercury_anderson2010dsha_bin_start;
extern coeffStruct& _model_coeff_ness1975();
extern unsigned char *_binary_coeffs_mercury_ness1975_bin_start;
extern coeffStruct& _model_coeff_uno2009();
extern unsigned char *_binary_coeffs_mercury_uno2009_bin_start;
extern coeffStruct& _model_coeff_anderson2010r();
extern unsigned char *_binary_coeffs_mercury_anderson2010r_bin_start;
extern coeffStruct& _model_coeff_thebault2018m2();
extern unsigned char *_binary_coeffs_mercury_thebault2018m2_bin_start;
extern coeffStruct& _model_coeff_ah5();
extern unsigned char *_binary_coeffs_uranus_ah5_bin_start;
extern coeffStruct& _model_coeff_gsfcq3full();
extern unsigned char *_binary_coeffs_uranus_gsfcq3full_bin_start;
extern coeffStruct& _model_coeff_gsfcq3();
extern unsigned char *_binary_coeffs_uranus_gsfcq3_bin_start;
extern coeffStruct& _model_coeff_umoh();
extern unsigned char *_binary_coeffs_uranus_umoh_bin_start;
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




/* This structure will store the Schmidt coefficients */
struct schmidtcoeffs {
	int n;
	int m;
	double g;
	double h;
};


/***********************************************************************
 * NAME : class Internal
 * 
 * DESCRIPTION : 
 * 		Class which will store the g and h spherical harmonic 
 * 		coefficients for a given model. To obtain the magnetic field,
 * 		use the Field() and FieldCart() member functions.
 * 
 * ********************************************************************/
class Internal {
	public:
		Internal(unsigned char *);
		Internal(const char *);
		Internal(const Internal&);
		~Internal();
	
		/*these four functions will calculate the field in spherical
		 * polar RH system III coordinates.*/
		void Field(int,double*,double*,double*,double*,double*,double*);
		void Field(int,double*,double*,double*,int,double*,double*,double*);
		void Field(double,double,double,double*,double*,double*);
		void Field(double,double,double,int,double*,double*,double*);
		
		/* these will be Cartesian */
		void FieldCart(double,double,double,double*,double*,double*);
		void FieldCart(double,double,double,int,double*,double*,double*);

		/* set current degree */
		void SetDegree(int n);
		int GetDegree();

		
	private:
		/*Schmidt coefficients */
		struct schmidtcoeffs *schc_;
		int nschc_;
		double **Snm_;
		
		/* maximum, default and current degree */
		int nmax_;
		int ndef_;
		int *ncur_;
		
		/* these ones will have Snm_ already multiplied */
		double **g_;
		double **h_;
		
		/* Legendre Polynomial and derivative arrays */
		double **Pnm_, **dPnm_;
		
		/* cosmp and sinmp arrays */
		double *cosmp_, *sinmp_;		
		
		
		/* hack to scale r or x,y,z because some models use a different
		 * definition for the planetary radius - notably the different 
		 * Jupiter models - this should be rpgood/rpbad, where rpgood
		 * is the accepted planetary radius and rpbad is the erroneous
		 * one - this will be then multiplied by r: rnew = r*rscale_
		 * where rscale_ = rgood/rbad */
		double rscale_;
		
		/* functions for initializing the object */
		void _LoadSchmidt(unsigned char*);
		void _LoadSchmidt(coeffStruct );
		void _Schmidt();
		void _CoeffGrids();

		/* This function will calculate the Legendre polynomials */
		void _Legendre(int,double*,double*,int,double***,double***);
		void _Legendre(double,double,int,double**,double**);
		
		/* this function will calculate the magnetic field components in
		 * spherical polar coordinates */
		void _SphHarm(int,double*,double*,double*,double*,double*,double*);
		/* could do with writing a scalar version of this for extra speed */
		void _SphHarm(double,double,double,double*,double*,double*);
		
		void _Cart2Pol(double,double,double,double*,double*,double*);
		void _BPol2BCart(double,double,double,double,double,double*,double*,double*);
		
		bool copy;

		/* initialization */
		bool useptr_;
		bool *init_;
		unsigned char *modelptr_;
		coeffStruct *modelstr_;
		void _Init();
		void _CheckInit();
	
};



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
extern Internal& spv();
extern Internal& soi();
extern Internal& v2();
extern Internal& cassini3();
extern Internal& cassini5();
extern Internal& z3();
extern Internal& burton2009();
extern Internal& v1();
extern Internal& cassini11();
extern Internal& p1184();
extern Internal& p11as();
extern Internal& kivelson2002b();
extern Internal& kivelson2002a();
extern Internal& kivelson2002c();
extern Internal& weber2022dip();
extern Internal& weber2022quad();
extern Internal& mh2014();
extern Internal& cain2003();
extern Internal& langlais2019();
extern Internal& gao2021();
extern Internal& igrf1935();
extern Internal& igrf2005();
extern Internal& igrf2000();
extern Internal& igrf1950();
extern Internal& igrf1960();
extern Internal& igrf1985();
extern Internal& igrf1945();
extern Internal& igrf1965();
extern Internal& igrf1905();
extern Internal& igrf2010();
extern Internal& igrf2020();
extern Internal& igrf1910();
extern Internal& igrf1990();
extern Internal& igrf2015();
extern Internal& igrf1925();
extern Internal& igrf2025();
extern Internal& igrf1970();
extern Internal& igrf1930();
extern Internal& igrf1920();
extern Internal& igrf1955();
extern Internal& igrf1995();
extern Internal& igrf1900();
extern Internal& igrf1980();
extern Internal& igrf1940();
extern Internal& igrf1975();
extern Internal& igrf1915();
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
}


/* based upon https://www.lonecpluspluscoder.com/2015/08/13/an-elegant-way-to-extract-keys-from-a-c-map/ */
/***********************************************************************
 * NAME : vector<> listMapKeys(inmap)
 * 
 * DESCRIPTION : List the keys used for a std::map.
 * 
 * INPUTS : 
 * 		map		inmap		std::map instance			
 * 
 * 
 * RETURNS :
 * 		vector	keys		vector object containing a list of the map 
 * 							keys
 * 
 * 
 * 
 * ********************************************************************/
template <typename Tkey, typename Tval> 
std::vector<Tkey> listMapKeys(std::map<Tkey,Tval> const &inmap) {
	std::vector<Tkey> keys;
	for (auto const& element: inmap) {
		keys.push_back(element.first);
	}
	return keys;
}	



/***********************************************************************
 * NAME : class InternalModel
 * 
 * DESCRIPTION : 
 * 		Class which can access all instances of Internal objects.
 * 
 * ********************************************************************/
class InternalModel {
	
	public:
		/* constructor */
		InternalModel();
		
		/* copy constructor */
		InternalModel(const InternalModel&);
		
		/* destructor */
		~InternalModel();
		
		/* Init this function - I would like to remove this if at all possible*/
		void CheckInit();
		void Init();
		
		/* set model parameters */
		void SetCartIn(bool);
		void SetCartOut(bool);
		bool GetCartIn();
		bool GetCartOut();
		void SetModel(const char *);
		void GetModel(char *);
		void SetDegree(int n);
		int GetDegree();

		/* Field functions */
		void Field(int,double*,double*,double*,int,double*,double*,double*);
		void Field(int,double*,double*,double*,double*,double*,double*);
		void Field(double,double,double,int,double*,double*,double*);
		void Field(double,double,double,double*,double*,double*);
				
		/* these objects are the models to use */
		std::map<std::string,Internal*> Models_;
		std::vector<std::string> ModelNames_;

	private:
		Internal *CurrentModel_;
		std::string *CurrentModelName_;


		/* coordinate/field vector rotation */
		bool copy_;
		bool *init_;
		bool *CartIn_;
		bool *CartOut_;
		void _Cart2Pol(int,double*,double*,double*,double*,double*,double*);
		void _Cart2Pol(double,double,double,double*,double*,double*);
		void _BPol2BCart(int,double*,double*,double*,double*,double*,double*,double*,double*);
		void _BPol2BCart(double,double,double,double,double,double*,double*,double*);
};



/* we want to initialize the model objects witht heir parameters */
InternalModel getInternalModel();

extern "C" {
}
#endif
#endif
