#include "mars_rover.h"

#include <gtest/gtest.h>

TEST(MarsRover, StaysInInitialLocation)
{
    auto initial_location = Location(0, 0, 'N');
    auto rover            = MarsRover(initial_location);
    rover.move("");

    EXPECT_EQ(rover.location, initial_location);
}
