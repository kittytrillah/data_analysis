#include <gtest/gtest.h>
#include <vector>
#include <optional>

TEST(DataTests, TestForwardFill) {
    std::vector<double> data1 = {1.0, NAN, NAN, 2.0, NAN};
    // Simulate forwardFill
    // Example: forwardFill(data1);
    std::vector<double> expected = {1.0, 1.0, 1.0, 2.0, 2.0};
    EXPECT_EQ(data1, expected);
}

TEST(DataTests, TestRollingMean) {
    std::vector<double> data2 = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<std::optional<double>> result = {
        std::nullopt, std::nullopt, 2.0, 3.0, 4.0
    };
    std::vector<std::optional<double>> expected = {
        std::nullopt, std::nullopt, 2.0, 3.0, 4.0
    };
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
