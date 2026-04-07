#include "schmidt.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

namespace {

bool NearlyEqual(double a, double b, double rel_tol) {
    const double diff = std::fabs(a - b);
    const double scale = std::fmax(std::fabs(a), std::fabs(b));
    if (scale == 0.0) {
        return diff == 0.0;
    }
    return diff <= rel_tol * scale;
}

double SchmidtExpectedOldSafe(int n, int m) {
    const int max_fact = n + m;
    std::vector<double> facts(static_cast<std::size_t>(max_fact + 1), 1.0);
    for (int i = 1; i <= max_fact; i++) {
        facts[static_cast<std::size_t>(i)] = static_cast<double>(i) * facts[static_cast<std::size_t>(i - 1)];
    }

    const double delta = (m == 0) ? 1.0 : 2.0;
    const double ratio = facts[static_cast<std::size_t>(n - m)] /
                         facts[static_cast<std::size_t>(n + m)];
    return std::sqrt(delta * ratio);
}

double SchmidtExpected(int n, int m) {
    const double delta = (m == 0) ? 1.0 : 2.0;
    const double log_ratio = std::lgamma(static_cast<double>(n - m + 1)) -
                             std::lgamma(static_cast<double>(n + m + 1));
    return std::sqrt(delta * std::exp(log_ratio));
}

} // namespace

int main() {
    const int nmax = 134;
    const std::vector<double> schmidt = ComputeSchmidtFlat(nmax);

    // This pair crosses the double-factorial overflow threshold in the old code:
    // (n + m)! = 180! would become inf with direct factorial accumulation.
    const int n = 120;
    const int m = 60;
    const double got = schmidt[SchmidtIndex(n, m)];
    const double expected = SchmidtExpected(n, m);

    if (!std::isfinite(got)) {
        std::cerr << "ComputeSchmidtFlat produced non-finite value at n=" << n
                  << ", m=" << m << '\n';
        return EXIT_FAILURE;
    }

    if (got == 0.0) {
        std::cerr << "ComputeSchmidtFlat produced zero at n=" << n
                  << ", m=" << m << " where positive value is expected\n";
        return EXIT_FAILURE;
    }

    if (!NearlyEqual(got, expected, 1.0e-12)) {
        std::cerr << "ComputeSchmidtFlat mismatch at n=" << n
                  << ", m=" << m << ": got=" << got
                  << ", expected=" << expected << '\n';
        return EXIT_FAILURE;
    }

    // For safe ranges, verify compatibility with the old direct-factorial logic.
    const std::vector<std::pair<int, int>> safe_pairs = {
        {1, 0},
        {2, 1},
        {5, 3},
        {10, 5},
        {20, 10},
        {40, 20},
    };

    for (const auto &[sn, sm] : safe_pairs) {
        const double new_val = schmidt[SchmidtIndex(sn, sm)];
        const double old_val = SchmidtExpectedOldSafe(sn, sm);
        if (!NearlyEqual(new_val, old_val, 1.0e-13)) {
            std::cerr << "New Schmidt value differs from old safe-factorial logic at n="
                      << sn << ", m=" << sm
                      << ": new=" << new_val
                      << ", old=" << old_val << '\n';
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
