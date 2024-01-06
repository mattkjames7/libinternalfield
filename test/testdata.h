#ifndef __TESTDATA_H__
#define __TESTDATA_H__
#ifdef __cplusplus
    #include <fstream>
    #include <vector>
    #include <cstdint> 
    #include <filesystem>
    #include <iostream>
#else
    #include<stdlib.h>
#endif

#ifdef __cplusplus
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
#else
    void readVectorsC(
        const char *testFile,
        double *x, double *y, double *z, double *bx, double *by, double *bz
    );
#endif
#endif
