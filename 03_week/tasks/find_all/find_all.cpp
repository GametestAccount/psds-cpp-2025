#include <vector>

auto FindAll(const std::vector<int>& vec, bool (*f)(int)) {
    std::vector<size_t> res;
    
    if (vec.empty() || !f) {
        return res;
    }

    size_t count = 0;

    for (size_t i = 0; i < vec.size(); ++i) {
        if (f(vec[i])) {
            ++count;
        }
    }

    res.reserve(count);

    for (size_t i = 0; i < vec.size(); ++i) {
        if (f(vec[i])) {
            res.push_back(i);
        }
    }

    return res;
}