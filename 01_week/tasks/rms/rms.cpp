#include <cstddef>
#include <cmath>

double CalculateRMS(double values[], size_t size) {
    if (values == nullptr || !size)
        return 0.0;
    
    double sum = 0.0;
    
    for (size_t i = 0; i < size; ++i)
        sum += values[i] * values[i];

    return std::sqrt(sum / size);
}
