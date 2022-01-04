#pragma once

#include "Base.hpp"

namespace TI4Echelon {

/// \brief Time duration.
class Duration {

public:

  /// \brief Default constructor. Initializes the duration to zero.
  Duration() noexcept {}

  /// \brief Constructor from a string of the form 1h05m or any subset of this form, such as 1h or 5m.
  Duration(const std::string& text) noexcept {
    if (!text.empty()) {
      std::string first_digits;
      char first_character{'\0'};
      std::string second_digits;
      char second_character{'\0'};
      for (const char c : text) {
        if (::isdigit(c)) {
          if (first_character == '\0') {
            first_digits += c;
          } else {
            second_digits += c;
          }
        } else if (c == 'h' || c == 'm') {
          if (first_character == '\0') {
            first_character = c;
          } else if (second_character == '\0') {
            second_character = c;
          } else {
            parsing_error(text);
          }
        } else {
          parsing_error(text);
        }
      }
      if (first_digits.empty() || first_character == '\0') {
        parsing_error(text);
      }
      const std::optional<int64_t> optional_first_number{string_to_integer_number(first_digits)};
      if (optional_first_number.has_value() && optional_first_number.value() >= 0) {
        if (first_character == 'h') {
          value_minutes_ = optional_first_number.value() * 60;
        } else if (first_character == 'm') {
          value_minutes_ = optional_first_number.value();
        }
      } else {
        parsing_error(text);
      }
      if (!second_digits.empty()) {
        if (second_character == 'm') {
          const std::optional<int64_t> optional_second_number{string_to_integer_number(second_digits)};
          if (optional_second_number.has_value() && optional_second_number.value() >= 0) {
            value_minutes_ += optional_second_number.value();
          } else {
            parsing_error(text);
          }
        } else {
          parsing_error(text);
        }
      }
    } else {
      parsing_error(text);
    }
  }

  double value_hours() const noexcept {
    return static_cast<double>(value_minutes_) / 60.0;
  }

  int64_t value_minutes() const noexcept {
    return value_minutes_;
  }

  /// \brief Prints the time duration in the form 1h05m.
  std::string print() const noexcept {
    const int64_t remainder{value_minutes_ % 60};
    return std::to_string(value_minutes_ / 60) + "h" + (remainder < 10 ? "0" : "") + std::to_string(remainder) + "m";
  }

private:

  int64_t value_minutes_{0};

  void parsing_error(const std::string& text) const noexcept {
    error("'" + text + "' is not a valid time duration.");
  }

}; // class Duration

} // namespace TI4Echelon
