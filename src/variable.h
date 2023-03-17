#ifndef __VARIABLE_H__
#define __VARIABLE_H__
#include <string>
#include <array>

#include "coeffs.h"

typedef struct variableModelList {
	std::string Name;
	std::array<std::string> Models;
	std::array<int> Date;
	std::array<double> ut;
	std::array<double> unixt;
	std::array<coeffStruct> modelCoeffs;
} variableModelList;

typedef variableModelList& (*variableModelListFunc)();



#endif