#pragma once

#include "Base.hpp"

namespace TI4Echelon {

/// \brief Integer number of victory points.
class VictoryPoints {

public:

  /// \brief Default constructor. Initializes to 0.
  constexpr VictoryPoints() noexcept {}

  /// \brief Constructor to a given value. For example, VictoryPoints{10} sets the value to 10.
  constexpr VictoryPoints(const int64_t value) noexcept : value_(value) {}

  constexpr int64_t value() const noexcept {
    return value_;
  }

  std::string print() const noexcept {
    return std::to_string(value_);
  }

  constexpr bool operator==(const VictoryPoints other) const noexcept {
    return value_ == other.value_;
  }

  constexpr bool operator!=(const VictoryPoints other) const noexcept {
    return value_ != other.value_;
  }

  constexpr bool operator<(const VictoryPoints other) const noexcept {
    return value_ < other.value_;
  }

  constexpr bool operator<=(const VictoryPoints other) const noexcept {
    return value_ <= other.value_;
  }

  constexpr bool operator>(const VictoryPoints other) const noexcept {
    return value_ > other.value_;
  }

  constexpr bool operator>=(const VictoryPoints other) const noexcept {
    return value_ >= other.value_;
  }

  constexpr VictoryPoints operator+(const VictoryPoints& other) const noexcept {
    return {value_ + other.value_};
  }

  constexpr VictoryPoints operator+(const int64_t number) const noexcept {
    return {value_ + number};
  }

  constexpr void operator+=(const VictoryPoints& other) noexcept {
    value_ += other.value_;
  }

  constexpr void operator+=(const int64_t number) noexcept {
    value_ += number;
  }

  constexpr VictoryPoints operator-(const VictoryPoints& other) const noexcept {
    return {value_ - other.value_};
  }

  constexpr VictoryPoints operator-(const int64_t number) const noexcept {
    return {value_ - number};
  }

  constexpr void operator-=(const VictoryPoints& other) noexcept {
    value_ -= other.value_;
  }

  constexpr void operator-=(const int64_t number) noexcept {
    value_ -= number;
  }

  constexpr VictoryPoints operator*(const int64_t number) const noexcept {
    return {value_ * number};
  }

  constexpr void operator*=(const int64_t number) noexcept {
    value_ *= number;
  }

  constexpr VictoryPoints operator/(const int64_t number) const noexcept {
    return {value_ / number};
  }

  constexpr void operator/=(const int64_t number) noexcept {
    value_ /= number;
  }

  struct sort_ascending {
    bool operator()(const VictoryPoints& points_1, const VictoryPoints& points_2) const noexcept {
      return points_1.value() < points_2.value();
    }
  };

  struct sort_descending {
    bool operator()(const VictoryPoints& points_1, const VictoryPoints& points_2) const noexcept {
      return points_1.value() > points_2.value();
    }
  };

private:

  int64_t value_{0};

}; // class VictoryPoints

/// \brief Games are typically played to 10-14 victory points. However, a custom game could be played to as few as 1 vitory point.
constexpr const VictoryPoints MinimumVictoryPoints{1};

/// \brief Games are typically played to 10-14 victory points. However, a custom game could be played to as much as 20 vitory points.
constexpr const VictoryPoints MaximumVictoryPoints{20};

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::VictoryPoints> {

    size_t operator()(const TI4Echelon::VictoryPoints& points) const {
      return hash<int64_t>()(points.value());
    }

  };

} // namespace std
