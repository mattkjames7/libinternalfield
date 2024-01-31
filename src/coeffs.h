#ifndef __COEFFS_H__
#define __COEFFS_H__
#include <vector>
#include <string>
#include <map>


typedef struct {
    const std::string name;
    const std::string body;
    const int len;
    const int nmax;
    const int ndef;
    const double rscale;
    const std::vector<int> n;
    const std::vector<int> m;
    const std::vector<double> g;
    const std::vector<double> h;
} coeffStruct;

typedef coeffStruct& (*coeffStructFunc)();

/* list of model names */
std::vector<std::string> getModelNames();

/* functions to return model coefficients */extern coeffStruct& _model_coeffspv();
extern coeffStruct& _model_coeffz3();
extern coeffStruct& _model_coeffcassini11();
extern coeffStruct& _model_coeffcassini5();
extern coeffStruct& _model_coeffsoi();
extern coeffStruct& _model_coeffp1184();
extern coeffStruct& _model_coeffburton2009();
extern coeffStruct& _model_coeffv1();
extern coeffStruct& _model_coeffcassini3();
extern coeffStruct& _model_coeffv2();
extern coeffStruct& _model_coeffp11as();
extern coeffStruct& _model_coeffigrf1960();
extern coeffStruct& _model_coeffigrf1935();
extern coeffStruct& _model_coeffigrf1945();
extern coeffStruct& _model_coeffigrf1925();
extern coeffStruct& _model_coeffigrf1910();
extern coeffStruct& _model_coeffigrf1905();
extern coeffStruct& _model_coeffigrf1980();
extern coeffStruct& _model_coeffigrf1990();
extern coeffStruct& _model_coeffigrf2015();
extern coeffStruct& _model_coeffigrf1940();
extern coeffStruct& _model_coeffigrf1930();
extern coeffStruct& _model_coeffigrf2005();
extern coeffStruct& _model_coeffigrf2020();
extern coeffStruct& _model_coeffigrf2010();
extern coeffStruct& _model_coeffigrf1915();
extern coeffStruct& _model_coeffigrf2000();
extern coeffStruct& _model_coeffigrf1950();
extern coeffStruct& _model_coeffigrf1970();
extern coeffStruct& _model_coeffigrf1965();
extern coeffStruct& _model_coeffigrf1920();
extern coeffStruct& _model_coeffigrf2025();
extern coeffStruct& _model_coeffigrf1985();
extern coeffStruct& _model_coeffigrf1975();
extern coeffStruct& _model_coeffigrf1955();
extern coeffStruct& _model_coeffigrf1900();
extern coeffStruct& _model_coeffigrf1995();
extern coeffStruct& _model_coeffgsfco8full();
extern coeffStruct& _model_coeffgsfco8();
extern coeffStruct& _model_coeffnmoh();
extern coeffStruct& _model_coeffkivelson2002a();
extern coeffStruct& _model_coeffweber2022quad();
extern coeffStruct& _model_coeffkivelson2002b();
extern coeffStruct& _model_coeffkivelson2002c();
extern coeffStruct& _model_coeffweber2022dip();
extern coeffStruct& _model_coeffuno2009();
extern coeffStruct& _model_coeffthebault2018m2();
extern coeffStruct& _model_coeffuno2009svd();
extern coeffStruct& _model_coeffanderson2010qts04();
extern coeffStruct& _model_coeffanderson2010dsha();
extern coeffStruct& _model_coeffanderson2012();
extern coeffStruct& _model_coeffanderson2010dts04();
extern coeffStruct& _model_coeffanderson2010qsha();
extern coeffStruct& _model_coeffness1975();
extern coeffStruct& _model_coeffthebault2018m1();
extern coeffStruct& _model_coeffanderson2010r();
extern coeffStruct& _model_coeffanderson2010d();
extern coeffStruct& _model_coeffanderson2010q();
extern coeffStruct& _model_coeffthebault2018m3();
extern coeffStruct& _model_coeffgao2021();
extern coeffStruct& _model_coeffcain2003();
extern coeffStruct& _model_coeffmh2014();
extern coeffStruct& _model_coefflanglais2019();
extern coeffStruct& _model_coeffgsfcq3full();
extern coeffStruct& _model_coeffgsfcq3();
extern coeffStruct& _model_coeffah5();
extern coeffStruct& _model_coeffumoh();
extern coeffStruct& _model_coeffjrm33();
extern coeffStruct& _model_coeffvit4();
extern coeffStruct& _model_coeffisaac();
extern coeffStruct& _model_coeffvipal();
extern coeffStruct& _model_coeffvip4();
extern coeffStruct& _model_coeffjpl15evs();
extern coeffStruct& _model_coeffp11a();
extern coeffStruct& _model_coeffjrm09();
extern coeffStruct& _model_coeffjpl15ev();
extern coeffStruct& _model_coeffo4();
extern coeffStruct& _model_coeffo6();
extern coeffStruct& _model_coeffsha();
extern coeffStruct& _model_coeffu17ev();
extern coeffStruct& _model_coeffgsfc15ev();
extern coeffStruct& _model_coeffgsfc13ev();
extern coeffStruct& _model_coeffgsfc15evs();
extern coeffStruct& _model_coeffv117ev();

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

#endif
