#include "mars_rover.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

struct MoveTestParams {
    Location    initial_location;
    std::string commands;
    Location    expected_location;
};

// Let Google Test know how to print MoveTestParams
std::ostream&
operator<<(std::ostream& os, const MoveTestParams& params)
{
    os << "initial_location: " << params.initial_location << ", "
       << "commands: \"" << params.commands << "\", "
       << "expected_location: " << params.expected_location;
    return os;
}

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
    OpportunitySingleRotateLeftTests, OpportunityTest,
    ::testing::Values(MoveTestParams{Location(0, 0, 'N'), "L", Location(0, 0, 'W')},
                      MoveTestParams{Location(0, 0, 'W'), "L", Location(0, 0, 'S')},
                      MoveTestParams{Location(0, 0, 'S'), "L", Location(0, 0, 'E')},
                      MoveTestParams{Location(0, 0, 'E'), "L", Location(0, 0, 'N')}));

INSTANTIATE_TEST_SUITE_P(
    OpportunitySingleRotateRightTests, OpportunityTest,
    ::testing::Values(MoveTestParams{Location(0, 0, 'N'), "R", Location(0, 0, 'E')},
                      MoveTestParams{Location(0, 0, 'E'), "R", Location(0, 0, 'S')},
                      MoveTestParams{Location(0, 0, 'S'), "R", Location(0, 0, 'W')},
                      MoveTestParams{Location(0, 0, 'W'), "R", Location(0, 0, 'N')}));
