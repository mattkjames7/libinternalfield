#include "scalegh.h"

#include "schmidt.h"

#include <stdexcept>

void ComputeScaledGH(
    const std::vector<int> &n,
    const std::vector<int> &m,
    const std::vector<double> &g,
    const std::vector<double> &h,
    const std::vector<double> &schmidtFlat,
    std::vector<double> &gScaled,
    std::vector<double> &hScaled
) {
    const std::size_t len = n.size();
    if (m.size() != len || g.size() != len || h.size() != len) {
        throw std::runtime_error("n/m/g/h arrays must have equal length");
    }

    gScaled.resize(len);
    hScaled.resize(len);

    for (std::size_t i = 0; i < len; i++) {
        const std::size_t idx = SchmidtIndex(n[i], m[i]);
        if (idx >= schmidtFlat.size()) {
            throw std::runtime_error("schmidt lookup out of range");
        }
        const double s = schmidtFlat[idx];
        gScaled[i] = g[i] * s;
        hScaled[i] = h[i] * s;
    }
}
