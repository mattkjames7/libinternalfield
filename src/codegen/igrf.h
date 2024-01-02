#ifndef __IGRF_H__
#define __IGRF_H__
#include <filesystem>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>
#include "savecoeffs.h"
#include "splitstring.h"


typedef struct {
    std::string name;
    std::vector<char> gh;
    std::vector<int> n;
    std::vector<int> m;
    std::vector<double> v;
} igrfModel;

void saveIGRFModels(std::filesystem::path dataPath);
#endif
