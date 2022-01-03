#pragma once

#include "Base.hpp"

namespace TI4Echelon {

class PlayerName {

public:

  PlayerName() noexcept {}

  PlayerName(const std::string& value) noexcept : value_(remove_non_alphabetic_characters(value)) {}

  const std::string& value() const noexcept {
    return value_;
  }

  bool operator==(const PlayerName& other) const noexcept {
    return value_ == other.value_;
  }

  bool operator!=(const PlayerName& other) const noexcept {
    return value_ != other.value_;
  }

  bool operator<(const PlayerName& other) const noexcept {
    return value_ < other.value_;
  }

  bool operator<=(const PlayerName& other) const noexcept {
    return value_ <= other.value_;
  }

  bool operator>(const PlayerName& other) const noexcept {
    return value_ > other.value_;
  }

  bool operator>=(const PlayerName& other) const noexcept {
    return value_ >= other.value_;
  }

  /// \brief Sort alphabetically.
  struct sort {
    bool operator()(const PlayerName& player_name_1, const PlayerName& player_name_2) const noexcept {
      return player_name_1.value() < player_name_2.value();
    }
  };

private:

  std::string value_;

}; // class PlayerName

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::PlayerName> {

    size_t operator()(const TI4Echelon::PlayerName& player_name) const {
      return hash<string>()(player_name.value());
    }

  };

} // namespace std
