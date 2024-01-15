
#ifndef __VARIABLE_H__
#define __VARIABLE_H__
#include <string>
#include <vector>
#include "coeffs.h"

typedef struct variableModelList {
	std::string name;
    std::string body;
	std::vector<std::string> models;
	std::vector<int> date;
	std::vector<double> ut;
	std::vector<double> unixt;
	std::vector<coeffStruct> coeffs;
} variableModelList;

typedef variableModelList& (*variableModelListFunc)();
variableModelList& _var_model_igrf();

#endif