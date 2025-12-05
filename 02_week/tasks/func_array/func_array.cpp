#include <cstddef>

double ApplyOperations(double a, double b, double (* const f[])(double, double), size_t length) {
    double sum = 0.0;

    if (!f || !length) {
        return sum;
    }

    for (size_t i = 0; i < length; i++) {
        if (f[i]) {
            sum += f[i](a, b);
        }
    }

    return sum;
}