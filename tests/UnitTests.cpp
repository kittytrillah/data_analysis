#include "DataPreprocessing.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>


int main() {
    using namespace finance;

    // Test forwardFill
    std::vector<double> data1 = {1.0, NAN, NAN, 2.0, NAN};
    DataPreprocessing::forwardFill(data1);
    assert(data1 == std::vector<double>{1.0, 1.0, 1.0, 2.0, 2.0});

    // Test rollingMean
    std::vector<double> data2 = {1.0, 2.0, 3.0, 4.0, 5.0};
    auto result = DataPreprocessing::rollingMean(data2, 3);
    assert(result == std::vector<std::optional<double>>{std::nullopt, std::nullopt, 2.0, 3.0, 4.0});

    // Test removeOutliers
    std::vector<double> data3 = {1.0, 2.0, 100.0, 3.0, 4.0};
    DataPreprocessing::removeOutliers(data3);
    assert(std::isnan(data3[2]));

    std::cout << "All tests passed!\n";
    return 0;
}