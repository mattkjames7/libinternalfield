#include "testdata.h"

void saveVector(std::ofstream &file, std::vector<double> &x) {

    std::int32_t size = static_cast<std::int32_t>(x.size());
    file.write(reinterpret_cast<const char*>(&size),sizeof(size));
    file.write(reinterpret_cast<const char*>(x.data()),x.size()*sizeof(double));
    
}

std::vector<double> readVector(std::ifstream &file) {

    std::int32_t size;
    file.read(reinterpret_cast<char*>(&size), sizeof(size));
    std::vector<double> x(size);
    file.read(reinterpret_cast<char*>(x.data()), size * sizeof(double));
    return x;
}

void saveVectors(
    std::filesystem::path &testFile,
    std::vector<double> &x, std::vector<double> &y, std::vector<double> &z,
    std::vector<double> &bx, std::vector<double> &by, std::vector<double> &bz
) {
    std::ofstream file(testFile,std::ios::binary);

    saveVector(file,x);
    saveVector(file,y);
    saveVector(file,z);

    saveVector(file,bx);
    saveVector(file,by);
    saveVector(file,bz);

    file.close();
}

void readVectors(
    std::filesystem::path &testFile,
    std::vector<double> &x, std::vector<double> &y, std::vector<double> &z,
    std::vector<double> &bx, std::vector<double> &by, std::vector<double> &bz
) {
    std::ifstream file(testFile,std::ios::binary);

    x = readVector(file);
    y = readVector(file);
    z = readVector(file);

    bx = readVector(file);
    by = readVector(file);
    bz = readVector(file);

    file.close();
}

void saveVectorVector(
    std::ofstream &file,
    std::vector<std::vector<double>> &x
    ) {

    int n = x.size();

    std::int32_t size = static_cast<std::int32_t>(x.size());
    file.write(reinterpret_cast<const char*>(&size),sizeof(size));
    for (int i=0;i<n;i++) {
        saveVector(file,x[i]);
    }


}

std::vector<std::vector<double>> readVectorVector(std::ifstream &file) {

    std::vector<double> tmp;
    std::vector<std::vector<double>> out;

    std::int32_t n;
    file.read(reinterpret_cast<char*>(&n), sizeof(n));

    for (int i=0;i<n;i++) {
        tmp = readVector(file);
        out.push_back(tmp);
        tmp.clear();
    }
    return out;
}


void saveModelVariables(
    std::filesystem::path &testFile,
    std::vector<std::vector<double>> &Snm,
    std::vector<std::vector<double>> &g,
    std::vector<std::vector<double>> &h
) {
    
    std::ofstream file(testFile,std::ios::binary);

    saveVectorVector(file,Snm);
    saveVectorVector(file,g);
    saveVectorVector(file,h);

    file.close();

}

void readModelVariables(
    std::filesystem::path &testFile,
    std::vector<std::vector<double>> &Snm,
    std::vector<std::vector<double>> &g,
    std::vector<std::vector<double>> &h
) {

    std::ifstream file(testFile,std::ios::binary);

    Snm = readVectorVector(file);
    g = readVectorVector(file);
    h = readVectorVector(file);

    file.close();

}

void readVectorsC(
    const char *testFile,
    double *x, double *y, double *z, double *bx, double *by, double *bz
) {

    std::filesystem::path filePath = testFile;
    int i;
    std::vector<double> vx, vy, vz, vbx, vby, vbz;

    readVectors(filePath,vx,vy,vz,vbx,vby,vbz);
    int n = vx.size();

    x = (double*) malloc(sizeof(double)*n);
    y = (double*) malloc(sizeof(double)*n);
    z = (double*) malloc(sizeof(double)*n);

    bx = (double*) malloc(sizeof(double)*n);
    by = (double*) malloc(sizeof(double)*n);
    bz = (double*) malloc(sizeof(double)*n);


    for (i=0;i<n;i++) {
        x[i] = vx[i];
        y[i] = vy[i];
        z[i] = vz[i];

        bx[i] = vbx[i];
        by[i] = vby[i];
        bz[i] = vbz[i];
    }
}

bool compareVectors(
    std::vector<double> bx0, std::vector<double> by0, std::vector<double> bz0,
    std::vector<double> bx1, std::vector<double> by1, std::vector<double> bz1
) {
    int n = bx0.size();
    if ((bx1.size() != n) || (by1.size() != n) || (bz1.size() != n) || 
        (by0.size() != n) || (bz0.size() != n)) {
        return false;
    }

    int i;
    for (i=0;i<n;i++) {
        if ((bx0[i] != bx1[i]) || (by0[i] != by1[i]) || (bz0[i] != bz1[i])) {
            return false;
        }
    }
    return true;
}