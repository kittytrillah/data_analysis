#include "DataPreprocessing.hpp"
#include <omp.h> // OpenMP for parallelism
#include <vector>
#include <numeric>
#include <cmath>
#include <optional>
#include <algorithm>
#include <stdexcept> // Exception handling
#include <iostream>

namespace finance {

// Forward-fills NaN values with the most recent non-NaN value
void DataPreprocessing::forwardFill(std::vector<double>& data) {
    double lastValid = NAN;
    for (auto& value : data) {
        if (std::isnan(value)) {
            value = lastValid; // Replace NaN with last valid value
        } else {
            lastValid = value; // Update last valid value
        }
    }
}

// Calculates rolling mean over a given window size
std::vector<std::optional<double>> DataPreprocessing::rollingMean(const std::vector<double>& data, std::size_t window) {
    if (window == 0 || data.empty()) {
        throw std::invalid_argument("Window size must be greater than 0 and data cannot be empty.");
    }

    std::vector<std::optional<double>> result(data.size(), std::nullopt);

    // Calculate rolling mean
    #pragma omp parallel for if(data.size() > 1000) // Parallelize only for large datasets
    for (std::size_t i = 0; i < result.size(); ++i) {
        if (i >= window - 1) {
            result[i] = std::accumulate(data.begin() + (i - window + 1), data.begin() + i + 1, 0.0) / window;
        }
    }

    return result;
}

// Removes outliers exceeding the threshold number of standard deviations
void DataPreprocessing::removeOutliers(std::vector<double>& data, double threshold) {
    if (data.empty()) {
        throw std::invalid_argument("Data cannot be empty.");
    }

    // Compute mean
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    std::cout << "Mean: " << mean << "\n";

    // Compute standard deviation
    double sq_sum = std::accumulate(data.begin(), data.end(), 0.0, 
                                    [mean](double acc, double val) { return acc + (val - mean) * (val - mean); });
    double std_dev = std::sqrt(sq_sum / data.size());
    std::cout << "Standard Deviation: " << std_dev << "\n";

    double threshold_value = threshold * std_dev;
    std::cout << "Threshold * StdDev: " << threshold_value << "\n";

    // Replace outliers
    for (std::size_t i = 0; i < data.size(); ++i) {
        double deviation = std::abs(data[i] - mean);

        // Mark values exceeding the threshold as outliers
        if (deviation >= threshold_value - 1e-1) { // Adjusted tolerance
            std::cout << "Marking as outlier: data[" << i << "] = " << data[i] << "\n";
            data[i] = NAN; // Use NaN for better semantic meaning
        }
    }
}

} // namespace finance