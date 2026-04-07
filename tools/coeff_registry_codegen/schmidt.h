#ifndef COEFF_REGISTRY_CODEGEN_SCHMIDT_H
#define COEFF_REGISTRY_CODEGEN_SCHMIDT_H

#include <cstddef>
#include <vector>

std::size_t SchmidtFlatSize(int nmax);
std::size_t SchmidtIndex(int n, int m);
std::vector<double> ComputeSchmidtFlat(int nmax);

#endif
