#ifndef COEFF_REGISTRY_CODEGEN_SCALEGH_H
#define COEFF_REGISTRY_CODEGEN_SCALEGH_H

#include <vector>

void ComputeScaledGH(
    const std::vector<int> &n,
    const std::vector<int> &m,
    const std::vector<double> &g,
    const std::vector<double> &h,
    const std::vector<double> &schmidtFlat,
    std::vector<double> &gScaled,
    std::vector<double> &hScaled
);

#endif
