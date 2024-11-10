#include "mars_rover.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct MoveTestParams {
    Location    initial_location;
    std::string commands;
    Location    expected_location;
};

class OpportunityTest : public ::testing::TestWithParam<MoveTestParams> {
protected:
    Opportunity rover{GetParam().initial_location};
};

TEST_P(OpportunityTest, Move)
{
    const auto& params = GetParam();
    rover.move(params.commands);
    EXPECT_EQ(rover.location, params.expected_location);
}

INSTANTIATE_TEST_SUITE_P(OpportunityEmptyCommandsTest, OpportunityTest,
                         ::testing::Values(MoveTestParams{
                             Location(0, 0, 'N'), "", Location(0, 0, 'N')}));

INSTANTIATE_TEST_SUITE_P(
    OpportunityRotateLeftTests, OpportunityTest,
    ::testing::Values(MoveTestParams{Location(0, 0, 'N'), "L", Location(0, 0, 'W')},
                      MoveTestParams{Location(0, 0, 'W'), "L", Location(0, 0, 'S')},
                      MoveTestParams{Location(0, 0, 'S'), "L", Location(0, 0, 'E')},
                      MoveTestParams{Location(0, 0, 'E'), "L", Location(0, 0, 'N')}));
