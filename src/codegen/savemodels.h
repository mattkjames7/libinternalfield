#ifndef __SAVEMODELS_H__
#define __SAVEMODELS_H__
#include <filesystem>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>
#include "savecoeffs.h"

void saveModels(
    std::filesystem::path dataPath,
    std::filesystem::path srcPath
);

#endif
