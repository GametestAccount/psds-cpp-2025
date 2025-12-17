#include <vector>

void Filter(std::vector<int>& vec, bool (*f)(int)) {
    if (vec.empty() || !f) {
        return;
    }

    std::vector<int> filtered;

    filtered.reserve(vec.size());

    for (const auto& value : vec) {
        if (f(value)) {
            filtered.push_back(value);
        }
    }

    vec = filtered;
}