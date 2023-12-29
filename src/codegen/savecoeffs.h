#ifndef __SAVECOEFFS_H__
#define __SAVECOEFFS_H__
#include <filesystem>
#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <sstream>


typedef std::tuple<std::string,std::string,std::filesystem::path> ModelFileTuple;
typedef std::vector<ModelFileTuple> ModelFileTuples;
typedef std::vector<std::filesystem::path> FileList;

/* this is what will be ready in directly from the file */
typedef struct {
    char gh;
    int m;
    int n;
    double val;
} FileCoeff;
typedef std::vector<FileCoeff> FileCoeffs;
typedef std::tuple<FileCoeffs,double,int> FileParams;

/* this is what we want to convert to */
typedef struct {
    std::string name;
    std::string body;
    int len;
    int nmax;
    int ndef;
    double rscale;
    std::vector<int> n;
    std::vector<int> m;
    std::vector<double> g;
    std::vector<double> h;
} ModelDef;

void saveCoeffs(std::filesystem::path dataPath);
#endif
