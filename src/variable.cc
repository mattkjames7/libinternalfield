#include "variable.h"

/* Body : earth ---  Model : igrf */
variableModelList& _var_model_igrf() {
	static const std::string name = "igrf";
	static const std::string body = "earth";
	static const std::vector<std::string> models = {
		"igrf1900",
		"igrf1905",
		"igrf1910",
		"igrf1915",
		"igrf1920",
		"igrf1925",
		"igrf1930",
		"igrf1935",
		"igrf1940",
		"igrf1945",
		"igrf1950",
		"igrf1955",
		"igrf1960",
		"igrf1965",
		"igrf1970",
		"igrf1975",
		"igrf1980",
		"igrf1985",
		"igrf1990",
		"igrf1995",
		"igrf2000",
		"igrf2005",
		"igrf2010",
		"igrf2015",
		"igrf2020",
		"igrf2025",
	};
	static const std::vector<int> date = {
		19000101,
		19050101,
		19100101,
		19150101,
		19200101,
		19250101,
		19300101,
		19350101,
		19400101,
		19450101,
		19500101,
		19550101,
		19600101,
		19650101,
		19700101,
		19750101,
		19800101,
		19850101,
		19900101,
		19950101,
		20000101,
		20050101,
		20100101,
		20150101,
		20200101,
		20250101,
	};
	static const std::vector<double> ut = {
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,
		    0,

    };
    std::vector<double> unixt = getUnixTime(date,ut);
    std::vector<coeffStruct> coeffs = getModelCoeffs(models);
    static variableModelList out = {
        name,body,models,date,ut,unixt,coeffs
    };
    \treturn out;
};


#endif