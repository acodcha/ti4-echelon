#pragma once

#include "Base.hpp"

namespace TI4Echelon {

/// \brief General-purpose percentage value.
class Percentage {
public:
  /// \brief Default constructor. Initializes to 0%.
  constexpr Percentage() noexcept {}

  /// \brief Constructor to a given value. For example, Percentage{0.42} sets
  /// the value to 42%.
  constexpr Percentage(const double value) noexcept : value_(value) {}

  constexpr double value() const noexcept { return value_; }

  /// \brief Prints to a given number of decimals. For example,
  /// Percentage{0.42}.print() returns "42%".
  std::string print(const int8_t decimals = 0) const noexcept {
    if (value_ == 0.0) {
      return "0%";
    } else {
      const double value_100{value_ * 100};
      std::ostringstream stream;
      stream << std::fixed << std::setprecision(decimals) << value_100 << "%";
      return stream.str();
    }
  }

  constexpr bool operator==(const Percentage& other) const noexcept {
    return value_ == other.value_;
  }

  constexpr bool operator!=(const Percentage& other) const noexcept {
    return value_ != other.value_;
  }

  constexpr bool operator<(const Percentage& other) const noexcept {
    return value_ < other.value_;
  }

  constexpr bool operator<=(const Percentage& other) const noexcept {
    return value_ <= other.value_;
  }

  constexpr bool operator>(const Percentage& other) const noexcept {
    return value_ > other.value_;
  }

  constexpr bool operator>=(const Percentage& other) const noexcept {
    return value_ >= other.value_;
  }

  constexpr Percentage operator+(const Percentage& other) const noexcept {
    return {value_ + other.value_};
  }

  constexpr Percentage operator+(const double number) const noexcept {
    return {value_ + number};
  }

  constexpr void operator+=(const Percentage& other) noexcept {
    value_ += other.value_;
  }

  constexpr void operator+=(const double number) noexcept { value_ += number; }

  constexpr Percentage operator-(const Percentage& other) const noexcept {
    return {value_ - other.value_};
  }

  constexpr Percentage operator-(const double number) const noexcept {
    return {value_ - number};
  }

  constexpr void operator-=(const Percentage& other) noexcept {
    value_ -= other.value_;
  }

  constexpr void operator-=(const double number) noexcept { value_ -= number; }

  constexpr Percentage operator*(const double number) const noexcept {
    return {value_ * number};
  }

  constexpr void operator*=(const double number) noexcept { value_ *= number; }

  constexpr Percentage operator/(const double number) const noexcept {
    return {value_ / number};
  }

  constexpr void operator/=(const double number) noexcept { value_ /= number; }

  /// \brief Sort descending, i.e. from highest percentage to lowest percentage.
  struct sort {
    bool operator()(const Percentage& percentage_1,
                    const Percentage& percentage_2) const noexcept {
      return percentage_1.value() > percentage_2.value();
    }
  };

private:
  double value_{0.0};

};  // class Percentage

}  // namespace TI4Echelon

namespace std {

template<> struct hash<TI4Echelon::Percentage> {
  size_t operator()(const TI4Echelon::Percentage& percentage) const {
    return hash<double>()(percentage.value());
  }
};

}  // namespace std
