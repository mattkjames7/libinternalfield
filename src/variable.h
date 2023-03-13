#ifndef __VARIABLE_H__
#define __VARIABLE_H__
#include <string>
#include <vector>

#include "coeffs.h"

typedef struct variableModelList {
	std::string Name;
	std::vector<std::string> Models;
	std::vector<int> Date;
	std::vector<double> ut;
	std::vector<double> unixt;
	std::vector<coeffStruct> modelCoeffs;
} variableModelList;

typedef variableModelList& (*variableModelListFunc)();



#endif