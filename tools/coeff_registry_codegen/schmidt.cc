#include "schmidt.h"

#include <cmath>
#include <stdexcept>

std::size_t SchmidtFlatSize(int nmax) {
    if (nmax < 0) {
        return 0;
    }
    return static_cast<std::size_t>(nmax + 1) * static_cast<std::size_t>(nmax + 2) / 2;
}

std::size_t SchmidtIndex(int n, int m) {
    if (n < 0 || m < 0 || m > n) {
        throw std::runtime_error("invalid (n,m) passed to SchmidtIndex");
    }
    return static_cast<std::size_t>(n) * static_cast<std::size_t>(n + 1) / 2 + static_cast<std::size_t>(m);
}

std::vector<double> ComputeSchmidtFlat(int nmax) {
    if (nmax < 0) {
        throw std::runtime_error("nmax must be >= 0");
    }

    const int nfact = 2 * nmax + 1;
    std::vector<double> facts(static_cast<std::size_t>(nfact), 1.0);
    for (int i = 1; i < nfact; i++) {
        facts[static_cast<std::size_t>(i)] = static_cast<double>(i) * facts[static_cast<std::size_t>(i - 1)];
    }

    std::vector<double> out(SchmidtFlatSize(nmax), 0.0);
    for (int n = 0; n <= nmax; n++) {
        for (int m = 0; m <= n; m++) {
            const double delta = (m == 0) ? 1.0 : 2.0;
            const double ratio = facts[static_cast<std::size_t>(n - m)] / facts[static_cast<std::size_t>(n + m)];
            out[SchmidtIndex(n, m)] = std::sqrt(delta * ratio);
        }
    }

    return out;
}
