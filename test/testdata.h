#ifndef __TESTDATA_H__
#define __TESTDATA_H__
#include <fstream>
#include <vector>
#include <cstdint> 
#include <filesystem>
#include <iostream>
#include<stdlib.h>


void saveVector(std::ofstream &file, std::vector<double> &x);
std::vector<double> readVector(std::ifstream &file);
void saveVectors(
    std::filesystem::path &testFile,
    std::vector<double> &x, std::vector<double> &y, std::vector<double> &z,
    std::vector<double> &bx, std::vector<double> &by, std::vector<double> &bz
);
void readVectors(
    std::filesystem::path &testFile,
    std::vector<double> &x, std::vector<double> &y, std::vector<double> &z,
    std::vector<double> &bx, std::vector<double> &by, std::vector<double> &bz
);
bool compareVectors(
    std::vector<double> bx0, std::vector<double> by0, std::vector<double> bz0,
    std::vector<double> bx1, std::vector<double> by1, std::vector<double> bz1
);

void readVectorsC(
    const char *testFile,
    double *x, double *y, double *z, double *bx, double *by, double *bz
);

#endif
