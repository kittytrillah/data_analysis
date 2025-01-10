#include "DataPreprocessing.hpp"
#include <numeric> // For std::accumulate
#include <algorithm> // For std::transform

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

    // Compute rolling mean using parallel execution
    std::for_each(std::execution::par, result.begin(), result.end(), [&](std::optional<double>& res, std::size_t i) {
        if (i >= window - 1) {
            res = std::accumulate(data.begin() + (i - window + 1), data.begin() + i + 1, 0.0) / window;
        }
    });

    return result;
}

void DataPreprocessing::removeOutliers(std::vector<double>& data, double threshold) {
    // Compute mean and standard deviation
    double mean = std::reduce(std::execution::par, data.begin(), data.end(), 0.0) / data.size();
    double sq_sum = std::transform_reduce(std::execution::par, data.begin(), data.end(), 0.0, std::plus<>(), [&](double val) {
        return (val - mean) * (val - mean);
    });
    double std_dev = std::sqrt(sq_sum / data.size());

    // Replace outliers with NaN
    std::transform(std::execution::par, data.begin(), data.end(), data.begin(), [&](double val) {
        return (std::abs(val - mean) > threshold * std_dev) ? NAN : val;
    });
}

} // namespace finance