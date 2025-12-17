#include <iostream>
#include <vector>
#include <utility>

struct Coord2D {
    int x = 0;
    int y = 0;
};

struct Circle {
    Coord2D coord;
    unsigned radius = 1;
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    return os << '(' << coord.x << ", " << coord.y << ')';
}

std::ostream& operator<<(std::ostream& os, const Circle& circ) {
    if (circ.radius == 0) {
        return os << "circle[]";
    }

    return os << "circle[" << circ.coord << ", r = " << circ.radius << "]";
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& reg) {
    os << ((reg.second) ? '+' : '-');
    return os << reg.first;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    if (list.empty()) {
        return os << "{}";
    }

    os << "{\n";

    for (auto it = list.begin(); it != list.end(); ++it) {
        os << '\t' << *it;

        if (it != list.end() - 1) {
            os << ',';
        }

        os << '\n';
    }

    os << '}';

    return os;
}