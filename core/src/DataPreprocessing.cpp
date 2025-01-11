#include "DataPreprocessing.hpp"
#include <omp.h> // Include OpenMP header
#include <vector>
#include <numeric>
#include <cmath>
#include <optional>
#include <algorithm>

namespace finance {

void DataPreprocessing::forwardFill(std::vector<double>& data) {
    std::optional<double> last_valid = std::nullopt;
    for (auto& val : data) {
        if (!std::isnan(val)) {
            last_valid = val;
        } else if (last_valid) {
            val = *last_valid;
        }
    }
}

std::vector<std::optional<double>> DataPreprocessing::rollingMean(const std::vector<double>& data, std::size_t window) {
    if (window == 0 || data.empty()) {
        throw std::invalid_argument("Window size must be greater than 0 and data cannot be empty");
    }

    std::vector<std::optional<double>> result(data.size(), std::nullopt);

    // Parallel loop using OpenMP
    #pragma omp parallel for
    for (std::size_t i = 0; i < result.size(); ++i) {
        if (i >= window - 1) {
            result[i] = std::accumulate(data.begin() + (i - window + 1), data.begin() + i + 1, 0.0) / window;
        }
    }

    return result;
}

void DataPreprocessing::removeOutliers(std::vector<double>& data, double threshold) {
    // Compute mean and standard deviation
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();

    double sq_sum = 0.0;
    #pragma omp parallel for reduction(+:sq_sum)
    for (std::size_t i = 0; i < data.size(); ++i) {
        sq_sum += (data[i] - mean) * (data[i] - mean);
    }
    double std_dev = std::sqrt(sq_sum / data.size());

    // Replace outliers with NaN
    #pragma omp parallel for
    for (std::size_t i = 0; i < data.size(); ++i) {
        if (std::abs(data[i] - mean) > threshold * std_dev) {
            data[i] = NAN;
        }
    }
}

} // namespace finance