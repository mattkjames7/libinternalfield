#ifndef __SAVELIBHEADER_H__
#define __SAVELIBHEADER_H__
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include "trimstring.h"

typedef std::pair<std::vector<std::string>, std::vector<std::string>>  StrVecPair;
void saveLibHeader(std::filesystem::path srcPath);
#endif
