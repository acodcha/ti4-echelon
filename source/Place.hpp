#pragma once

#include "Base.hpp"

namespace TI4Echelon {

/// \brief Finish place within a game, such as 1st, 2nd, 3rd, and so on.
class Place {

public:

  /// \brief Default constructor. Initializes to 0th place.
  constexpr Place() noexcept {}

  /// \brief Constructor to a given value. For example, Place{2} sets the value to 2nd place.
  constexpr Place(const int8_t value) noexcept : value_(value) {}

  /// \brief Constructor from a string. Expects text such as "1st", "2nd", and so on.
  Place(const std::string& text) noexcept {
    if (text == "1st") {
      value_ = 1;
    } else if (text == "2nd") {
      value_ = 2;
    } else if (text == "3rd") {
      value_ = 3;
    } else {
      std::string digits;
      std::string letters;
      for (std::string::const_iterator index = text.cbegin(); index < text.cend(); ++index) {
        if (::isdigit(*index)) {
          digits += *index;
        } else {
          letters += text.substr(index - text.cbegin());
          break;
        }
      }
      const std::optional<int64_t> optional_number{string_to_integer_number(digits)};
      if (letters == "th" && optional_number.has_value() && optional_number.value() >= 0 && optional_number.value() <= std::numeric_limits<int8_t>::max()) {
        value_ = static_cast<int8_t>(optional_number.value());
      } else {
        error("'" + text + "' is not a valid place.");
      }
    }
  }

  constexpr int8_t value() const noexcept {
    return value_;
  }

  std::string print() const noexcept {
    if (value_ == 1) {
      return "1st";
    } else if (value_ == 2) {
      return "2nd";
    } else if (value_ == 3) {
      return "3rd";
    } else {
      return std::to_string(value_) + "th";
    }
  }

  /// \brief The outcome of a game between a pair of players is 1, 0.5, or 0 in the case of a higher place, an equal place, or a lower place than the opponent, respectively.
  double outcome(const Place& opponent_place) const noexcept {
    // A "lower" place is better. For example, 1st place is better than 2nd place.
    if (*this < opponent_place) {
      return 1.0;
    } else if (*this > opponent_place) {
      return 0.0;
    } else {
      // This case is included for completeness even though equal places cannot occur.
      return 0.5;
    }
  }

  constexpr bool operator==(const Place& other) const noexcept {
    return value_ == other.value_;
  }

  constexpr bool operator!=(const Place& other) const noexcept {
    return value_ != other.value_;
  }

  constexpr bool operator<(const Place& other) const noexcept {
    return value_ < other.value_;
  }

  constexpr bool operator<=(const Place& other) const noexcept {
    return value_ <= other.value_;
  }

  constexpr bool operator>(const Place& other) const noexcept {
    return value_ > other.value_;
  }

  constexpr bool operator>=(const Place& other) const noexcept {
    return value_ >= other.value_;
  }

  /// \brief Prefix ++ operator.
  Place& operator++() {
    ++value_;
    return *this;
  }

  /// \brief Postfix ++ operator.
  Place operator++(int) {
    Place result(*this);
    ++(*this);
    return result;
  }

  /// \brief Prefix -- operator.
  Place& operator--() {
    --value_;
    return *this;
  }

  /// \brief Postfix -- operator.
  Place operator--(int) {
    Place result(*this);
    --(*this);
    return result;
  }

  /// \brief Sort ascending, i.e. from first place to last place.
  struct sort {
    bool operator()(const Place& place_1, const Place& place_2) const noexcept {
      return place_1.value() < place_2.value();
    }
  };

private:

  int8_t value_{0};

}; // class Place

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Place> {

    size_t operator()(const TI4Echelon::Place& place) const {
      return hash<int8_t>()(place.value());
    }

  };

} // namespace std
