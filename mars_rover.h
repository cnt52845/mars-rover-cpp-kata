#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>

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

    virtual void move(const std::string& commands) = 0;

    Location location;
};

class Opportunity : public MarsRover {
public:
    Opportunity() = delete;
    Opportunity(Location location) : MarsRover(location) {}

    void move(const std::string& commands) override
    {
        if (commands == "L") {
            location.orientation = rotate_left(location.orientation);
        }
        else if (commands == "R") {
            location.orientation = rotate_right(location.orientation);
        }
    }

protected:
    char rotate_left(char orientation) const
    {
        static const std::unordered_map<char, char> left_turns = {
            {'N', 'W'}, {'W', 'S'}, {'S', 'E'}, {'E', 'N'}};

        return left_turns.at(orientation);
    }

    char rotate_right(char orientation) const
    {
        static const std::unordered_map<char, char> right_turns = {
            {'N', 'E'}, {'E', 'S'}, {'S', 'W'}, {'W', 'N'}};

        return right_turns.at(orientation);
    }
};
