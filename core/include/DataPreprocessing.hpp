#ifndef DATAPREPROCESSING_HPP
#define DATAPREPROCESSING_HPP

#include <vector>
#include <optional>
#include <cmath>
#include <execution> // For parallel algorithms

namespace finance {

class DataPreprocessing {
public:
    // Fill missing values using a forward-fill method
    static void forwardFill(std::vector<double>& data);

    // Compute rolling mean over a window size
    static std::vector<std::optional<double>> rollingMean(const std::vector<double>& data, std::size_t window);

    // Detect and replace outliers using the z-score method
    static void removeOutliers(std::vector<double>& data, double threshold = 3.0);
};

} // namespace finance

#endif // DATAPREPROCESSING_HPP