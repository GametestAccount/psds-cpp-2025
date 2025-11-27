#include <cstddef>
#include <iostream>
#include <algorithm>
#include <string>

void PrintBits(long long value, size_t bytes) {
    if (bytes == 0 || bytes > 8) {
        return;
    }

    std::string bits;

    for (size_t i = 0, j = bytes * 8; i < j; i++) {
        if (value & (1LL << i)) {
            bits += '1';
        }
        else {
            bits += '0';
        }

        if (((i+1) % 4 == 0) && (i > 0) && (i < j - 1)) {
            bits += '\'';
        }
    }

    std::reverse(bits.begin(), bits.end());

    std::cout << "0b" << bits << '\n';
}
