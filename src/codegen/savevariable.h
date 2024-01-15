#ifndef __SAVEVARIABLE_H__
#define __SAVEVARIABLE_H__
#include <filesystem>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>
#include "listfiles.h"
#include "splitstring.h"

typedef std::tuple<std::string,std::string,std::filesystem::path> VariableModelTuple;
typedef std::vector<VariableModelTuple> VariableModelTuples;

typedef struct {
    std::string model;
    int date;
    double ut;
} VariableModelEntry;
typedef std::vector<VariableModelEntry> VariableModel;

void saveVariable(
    std::filesystem::path dataPath,
    std::filesystem::path srcPath
);
#endif
