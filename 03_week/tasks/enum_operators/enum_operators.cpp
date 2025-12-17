#include <cstdint>
#include <vector>
#include <iostream>

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

CheckFlags operator|(const CheckFlags& lhs, const CheckFlags& rhs) {
    uint8_t lhs_u = static_cast<uint8_t>(lhs);
    uint8_t rhs_u = static_cast<uint8_t>(rhs);
    uint8_t all_u = static_cast<uint8_t>(CheckFlags::ALL);

    return static_cast<CheckFlags>((lhs_u | rhs_u) & all_u);
}

bool operator&(const CheckFlags& lhs, const CheckFlags& rhs) {
    uint8_t all_u = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t none_u = static_cast<uint8_t>(CheckFlags::NONE);

    uint8_t lhs_u = static_cast<uint8_t>(lhs) & all_u;
    uint8_t rhs_u = static_cast<uint8_t>(rhs) & all_u;
    
    if ((lhs_u == none_u) || (rhs_u == none_u)) {
        return lhs_u & rhs_u;
    }

    return ((lhs_u & rhs_u) == rhs_u) || ((rhs_u & lhs_u) == lhs_u);
}

CheckFlags operator^(const CheckFlags& lhs, const CheckFlags& rhs) {
    uint8_t lhs_u = static_cast<uint8_t>(lhs);
    uint8_t rhs_u = static_cast<uint8_t>(rhs);
    uint8_t all_u = static_cast<uint8_t>(CheckFlags::ALL);

    return static_cast<CheckFlags>((lhs_u ^ rhs_u) & all_u);
}

CheckFlags operator~(const CheckFlags& other) {
    uint8_t other_u = static_cast<uint8_t>(other);
    uint8_t all_u = static_cast<uint8_t>(CheckFlags::ALL);

    return static_cast<CheckFlags>((~other_u) & all_u);
}

std::ostream& operator<<(std::ostream& lhs, const CheckFlags& rhs) {
    uint8_t all_u = static_cast<uint8_t>(CheckFlags::ALL);
    uint8_t rhs_u = static_cast<uint8_t>(rhs) & all_u;

    if (rhs_u == static_cast<uint8_t>(CheckFlags::NONE)) {
        return lhs << "NONE";
    }

    std::string flags = "";

    for (uint8_t i = 1; i < all_u; i <<= 1) {
        switch (static_cast<CheckFlags>(rhs_u & i)) {
            case CheckFlags::TIME:
                flags += "TIME, ";
                break;
            case CheckFlags::DATE:
                flags += "DATE, ";
                break;
            case CheckFlags::USER:
                flags += "USER, ";
                break;
            case CheckFlags::CERT:
                flags += "CERT, ";
                break;
            case CheckFlags::KEYS:
                flags += "KEYS, ";
                break;
            case CheckFlags::DEST:
                flags += "DEST, ";
                break;
        }
    }

    if (!flags.empty()) {
        flags.pop_back();
        flags.pop_back();
    }

    return lhs << flags;
}