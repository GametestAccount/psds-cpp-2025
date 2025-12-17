#include <vector>
#include <cstdlib>
#include <cmath>

std::vector<int> Range(int from, int to, int step = 1) {
    std::vector<int> res;

    if (!step) {
        return res;
    }

    if ((from > to) && (step > 0)) {
        return res;
    }

    if ((from < to) && (step < 0)) {
        return res;
    }

    size_t elements = std::abs(std::ceil((to - from) / (double)step));

    if (!elements) {
        return res;
    }

    res.reserve(elements);
    
    for (int i = from; (from < to) ? (i < to) : (i > to); i += step) {
        res.push_back(i);
    }

    return res;
}