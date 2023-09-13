#pragma once

#include "Base.hpp"

namespace TI4Echelon {

/// \brief Linear regression of x-y data.
class LinearRegression {
public:
  /// \brief Default constructor. Initializes to zero slope and zero intercept.
  constexpr LinearRegression() noexcept {}

  /// \brief Construct a linear regression from x-y data.
  LinearRegression(
      const std::vector<std::pair<double, double>>& x_y_data) noexcept {
    if (x_y_data.empty()) {
      // Do nothing.
    } else if (x_y_data.size() == 1) {
      intercept_ = x_y_data[0].second;
    } else {
      // Two or more data points.
      double n{static_cast<double>(x_y_data.size())};
      double sum_x{0.0};
      double sum_y{0.0};
      double sum_xx{0.0};
      double sum_xy{0.0};
      double sum_yy{0.0};
      for (const std::pair<double, double>& x_y : x_y_data) {
        sum_x += x_y.first;
        sum_y += x_y.second;
        sum_xx += x_y.first * x_y.first;
        sum_xy += x_y.first * x_y.second;
        sum_yy += x_y.second * x_y.second;
      }
      slope_ =
          ((n * sum_xy) - (sum_x * sum_y)) / ((n * sum_xx) - sum_x * sum_x);
      intercept_ = (sum_y - (slope_ * sum_x)) / n;
    }
  }

  constexpr double slope() const noexcept {
    return slope_;
  }

  constexpr double intercept() const noexcept {
    return intercept_;
  }

  /// \brief Use the linear regression to obtain y given x.
  double operator()(const double x) const noexcept {
    return intercept_ + slope_ * x;
  }

private:
  double slope_{0.0};

  double intercept_{0.0};

};  // class LinearRegression

}  // namespace TI4Echelon
