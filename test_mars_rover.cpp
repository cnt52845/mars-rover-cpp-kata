#include "mars_rover.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(OpportunityTest, GivenEmptyCommands_WhenMove_ThenLocationDoesNotChange)
{
    auto initial_location = Location(0, 0, 'N');
    auto rover            = Opportunity(initial_location);
    rover.move("");

    EXPECT_EQ(rover.location, initial_location);
}

TEST(OpportunityTest, GivenOrientationNorth_WhenTurnLeftOneTime_ThenOrientationWest)
{
    auto initial_location  = Location(0, 0, 'N');
    auto expected_location = Location(0, 0, 'W');
    auto rover             = Opportunity(initial_location);
    rover.move("L");

    EXPECT_EQ(rover.location, expected_location);
}
