#include <vector>
#include <cmath>

struct DataStats {
    double avg = 0.0;
    double sd = 0.0;
};

DataStats CalculateDataStats(const std::vector<int>& values) {
    DataStats data;

    if (values.empty()) {
        return data;
    }

    for (const auto& value : values) {
        data.avg += value;
    }

    data.avg /= values.size();

    for (const auto& value : values) {
        data.sd += std::pow(value - data.avg, 2);
    }

    data.sd = std::sqrt(data.sd / values.size());

    return data;
}
