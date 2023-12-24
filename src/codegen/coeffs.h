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

/* functions to return model coefficients */extern coeffStruc& _model_coeffspv();
extern coeffStruc& _model_coeffz3();
extern coeffStruc& _model_coeffcassini11();
extern coeffStruc& _model_coeffcassini5();
extern coeffStruc& _model_coeffsoi();
extern coeffStruc& _model_coeffp1184();
extern coeffStruc& _model_coeffburton2009();
extern coeffStruc& _model_coeffv1();
extern coeffStruc& _model_coeffcassini3();
extern coeffStruc& _model_coeffv2();
extern coeffStruc& _model_coeffp11as();
extern coeffStruc& _model_coeffigrf1960();
extern coeffStruc& _model_coeffigrf1935();
extern coeffStruc& _model_coeffigrf1945();
extern coeffStruc& _model_coeffigrf1925();
extern coeffStruc& _model_coeffigrf1910();
extern coeffStruc& _model_coeffigrf1905();
extern coeffStruc& _model_coeffigrf1980();
extern coeffStruc& _model_coeffigrf1990();
extern coeffStruc& _model_coeffigrf2015();
extern coeffStruc& _model_coeffigrf1940();
extern coeffStruc& _model_coeffigrf1930();
extern coeffStruc& _model_coeffigrf2005();
extern coeffStruc& _model_coeffigrf2020();
extern coeffStruc& _model_coeffigrf2010();
extern coeffStruc& _model_coeffigrf1915();
extern coeffStruc& _model_coeffigrf2000();
extern coeffStruc& _model_coeffigrf1950();
extern coeffStruc& _model_coeffigrf1970();
extern coeffStruc& _model_coeffigrf1965();
extern coeffStruc& _model_coeffigrf1920();
extern coeffStruc& _model_coeffigrf2025();
extern coeffStruc& _model_coeffigrf1985();
extern coeffStruc& _model_coeffigrf1975();
extern coeffStruc& _model_coeffigrf1955();
extern coeffStruc& _model_coeffigrf1900();
extern coeffStruc& _model_coeffigrf1995();
extern coeffStruc& _model_coeffgsfco8full();
extern coeffStruc& _model_coeffgsfco8();
extern coeffStruc& _model_coeffnmoh();
extern coeffStruc& _model_coeffkivelson2002a();
extern coeffStruc& _model_coeffweber2022quad();
extern coeffStruc& _model_coeffkivelson2002b();
extern coeffStruc& _model_coeffkivelson2002c();
extern coeffStruc& _model_coeffweber2022dip();
extern coeffStruc& _model_coeffuno2009();
extern coeffStruc& _model_coeffthebault2018m2();
extern coeffStruc& _model_coeffuno2009svd();
extern coeffStruc& _model_coeffanderson2010qts04();
extern coeffStruc& _model_coeffanderson2010dsha();
extern coeffStruc& _model_coeffanderson2012();
extern coeffStruc& _model_coeffanderson2010dts04();
extern coeffStruc& _model_coeffanderson2010qsha();
extern coeffStruc& _model_coeffness1975();
extern coeffStruc& _model_coeffthebault2018m1();
extern coeffStruc& _model_coeffanderson2010r();
extern coeffStruc& _model_coeffanderson2010d();
extern coeffStruc& _model_coeffanderson2010q();
extern coeffStruc& _model_coeffthebault2018m3();
extern coeffStruc& _model_coeffgao2021();
extern coeffStruc& _model_coeffcain2003();
extern coeffStruc& _model_coeffmh2014();
extern coeffStruc& _model_coefflanglais2019();
extern coeffStruc& _model_coeffgsfcq3full();
extern coeffStruc& _model_coeffgsfcq3();
extern coeffStruc& _model_coeffah5();
extern coeffStruc& _model_coeffumoh();
extern coeffStruc& _model_coeffjrm33();
extern coeffStruc& _model_coeffvit4();
extern coeffStruc& _model_coeffisaac();
extern coeffStruc& _model_coeffvipal();
extern coeffStruc& _model_coeffvip4();
extern coeffStruc& _model_coeffjpl15evs();
extern coeffStruc& _model_coeffp11a();
extern coeffStruc& _model_coeffjrm09();
extern coeffStruc& _model_coeffjpl15ev();
extern coeffStruc& _model_coeffo4();
extern coeffStruc& _model_coeffo6();
extern coeffStruc& _model_coeffsha();
extern coeffStruc& _model_coeffu17ev();
extern coeffStruc& _model_coeffgsfc15ev();
extern coeffStruc& _model_coeffgsfc13ev();
extern coeffStruc& _model_coeffgsfc15evs();
extern coeffStruc& _model_coeffv117ev();

#endif
