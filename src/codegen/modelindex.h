#ifndef __MODELINDEX_H__
#define __MODELINDEX_H__

#include <filesystem>
#include <string>
#include <tuple>
#include <vector>

#include "listfiles.h"

typedef std::tuple<std::string, std::string, std::filesystem::path> ModelFileTuple;
typedef std::vector<ModelFileTuple> ModelFileTuples;

ModelFileTuples listModels(const std::filesystem::path &coeffDir);

#endif
