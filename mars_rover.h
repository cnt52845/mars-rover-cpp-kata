#pragma once

#include <memory>
#include <iostream>
#include <string>

/**
 * A class template to express an equality comparison interface
 */
template <typename T> class EqualityComparable {
    friend bool operator==(const T& lhs, const T& rhs) { return lhs.equal_to(rhs); }
    friend bool operator!=(const T& lhs, const T& rhs) { return !lhs.equal_to(rhs); }
};

struct Location : private EqualityComparable<Location> {
    Location() = delete;
    Location(int x, int y, char orientation) : x(x), y(y), orientation(orientation) {}

    bool equal_to(const Location& other) const
    {
        return x == other.x && y == other.y && orientation == other.orientation;
    }

    int  x, y;
    char orientation;
};

// Let Google Test know how to print this
inline std::ostream&
operator<<(std::ostream& os, const Location& location)
{
    os << '(' << location.x << ',' << location.y << ',' << location.orientation << ')';
    return os;
}

class MarsRover {
public:
    MarsRover() = delete;
    MarsRover(Location location) : location(std::move(location)) {}

    void move(const std::string& commands) {}

    Location location;
};
