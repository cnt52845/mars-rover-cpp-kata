#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <utility>

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
    MarsRover(Location location) : location(std::move(location))
    {
        setIncrements(location.orientation);
    }

    void setIncrements(char orientation)
    {
        switch (orientation) {
        case 'N':
            dx = 0;
            dy = 1;
            break;
        case 'W':
            dx = -1;
            dy = 0;
            break;
        case 'E':
            dx = 1;
            dy = 0;
            break;
        default: // S
            dx = 0;
            dy = -1;
        }
    }

    void move(const std::string& commands)
    {
        static const char orientations[]   = {'N', 'W', 'S', 'E'};
        unsigned int      orientationIndex = 0;

        for (const char command : commands) {
            if (command == 'L') {
                orientationIndex++;
            }
            else if (command == 'R') {
                orientationIndex--;
            }
            else if (command == 'F') {
                this->location.x += dx;
                this->location.y += dy;
            }
            else if (command == 'B') {
                this->location.x -= dx;
                this->location.y -= dy;
            }
        }
        orientationIndex &= 3;
        location.orientation = orientations[orientationIndex];
        setIncrements(location.orientation);
    }

    Location location;
    int      dx;
    int      dy;
};
