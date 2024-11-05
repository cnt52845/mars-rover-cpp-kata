#include "mars_rover.h"

#include <gtest/gtest.h>

class MarsRoverTest : public ::testing::Test {
public:
    Location  initial_location = Location(0, 0, 'N');
    MarsRover rover            = MarsRover(initial_location);
};

TEST_F(MarsRoverTest, StaysInInitialLocation)
{
    rover.move("");

    EXPECT_EQ(rover.location, initial_location);
}

TEST_F(MarsRoverTest, When_passedInvalidDirection_Then_OrientationNotChanged)
{
    rover.move("X");

    EXPECT_EQ(rover.location, initial_location);
}

TEST_F(MarsRoverTest, PassL_When_OrientationNorth_Then_OrientationWest)
{
    Location expectedLocation = Location(0, 0, 'W');
    rover.move("L");

    EXPECT_EQ(rover.location, expectedLocation);
}

TEST_F(MarsRoverTest, PassR_When_OrientationNorth_Then_OrientationEast)
{
    Location expectedLocation = Location(0, 0, 'E');
    rover.move("R");

    EXPECT_EQ(rover.location, expectedLocation);
}

TEST_F(MarsRoverTest, PassRTwice_When_OrientationNorth_Then_OrientationSouth)
{
    Location expectedLocation = Location(0, 0, 'S');
    rover.move("RR");

    EXPECT_EQ(rover.location, expectedLocation);
}

TEST_F(MarsRoverTest, PassR3Times_When_OrientationNorth_Then_OrientationWest)
{
    Location expectedLocation = Location(0, 0, 'W');
    rover.move("RRR");

    EXPECT_EQ(rover.location, expectedLocation);
}

TEST_F(MarsRoverTest, PassL3Times_When_OrientationNorth_Then_OrientationEast)
{
    Location expectedLocation = Location(0, 0, 'E');
    rover.move("LLL");

    EXPECT_EQ(rover.location, expectedLocation);
}

TEST_F(MarsRoverTest, PassL4Times_When_OrientationNorth_Then_OrientationNorth)
{
    Location expectedLocation = Location(0, 0, 'N');
    rover.move("LLLL");

    EXPECT_EQ(rover.location, expectedLocation);
}

TEST_F(MarsRoverTest, MoveForwardsOne_WhenPassingF)
{
    rover.move("F");
    EXPECT_EQ(rover.location, Location(0, 1, 'N'));
}

TEST_F(MarsRoverTest, MoveBackwardsOne_WhenPassingB)
{
    MarsRover r(Location(1, 1, 'N'));
    r.move("B");
    EXPECT_EQ(r.location, Location(1, 0, 'N'));
}

TEST_F(MarsRoverTest, turn_and_move)
{
    MarsRover r(Location(1, 1, 'W'));
    r.move("F");
    EXPECT_EQ(r.location, Location(0, 1, 'W'));
}