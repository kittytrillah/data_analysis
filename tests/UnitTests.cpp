#include <gtest/gtest.h>
#include <vector>
#include <optional>
#include <cmath>
#include "DataPreprocessing.hpp"

using namespace finance; // Use the finance namespace

TEST(DataPreprocessingTests, TestForwardFill) {
    std::vector<double> data1 = {1.0, NAN, NAN, 2.0, NAN};
    DataPreprocessing::forwardFill(data1);

    std::vector<double> expected = {1.0, 1.0, 1.0, 2.0, 2.0};
    EXPECT_EQ(data1, expected);
}

TEST(DataPreprocessingTests, TestRollingMean) {
    std::vector<double> data2 = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto result = DataPreprocessing::rollingMean(data2, 3);

    std::vector<std::optional<double>> expected = {
        std::nullopt, std::nullopt, 2.0, 3.0, 4.0
    };
    EXPECT_EQ(result, expected);
}

TEST(DataPreprocessingTests, TestRemoveOutliers) {
    std::vector<double> data3 = {10.0, 12.0, 12.5, 13.0, 100.0}; // 100.0 is an outlier
    DataPreprocessing::removeOutliers(data3, 2.0);

    std::vector<double> expected = {10.0, 12.0, 12.5, 13.0, NAN}; // Marked as NaN
    for (std::size_t i = 0; i < data3.size(); ++i) {
        if (std::isnan(expected[i])) {
            EXPECT_TRUE(std::isnan(data3[i])) << "Index " << i << " should be NaN.";
        } else {
            EXPECT_EQ(data3[i], expected[i]) << "Mismatch at index " << i;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}