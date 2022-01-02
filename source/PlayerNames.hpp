#pragma once

#include "PlayerName.hpp"

namespace TI4Echelon {

/// \brief Set of player names.
class PlayerNames {

public:

  /// \brief Default constructor. Initializes to an empty set.
  PlayerNames() noexcept {}

  /// \brief Constructor that initializes the set to a single player name. Additional player names can be inserted later.
  PlayerNames(const PlayerName& player_name) noexcept {
    data_.insert(player_name);
  }

  std::string print() const noexcept {
    std::string text;
    for (const PlayerName& player_name : data_) {
      if (!text.empty()) {
        text += " ";
      }
      text += player_name.value();
    }
    return text;
  }

  struct iterator : public std::set<PlayerName, PlayerName::sort>::iterator {
    iterator(const std::set<PlayerName, PlayerName::sort>::iterator i) noexcept : std::set<PlayerName, PlayerName::sort>::iterator(i) {}
  };

  struct const_iterator : public std::set<PlayerName, PlayerName::sort>::const_iterator {
    const_iterator(const std::set<PlayerName, PlayerName::sort>::const_iterator i) noexcept : std::set<PlayerName, PlayerName::sort>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::set<PlayerName, PlayerName::sort>::reverse_iterator {
    reverse_iterator(const std::set<PlayerName, PlayerName::sort>::reverse_iterator i) noexcept : std::set<PlayerName, PlayerName::sort>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::set<PlayerName, PlayerName::sort>::const_reverse_iterator {
    const_reverse_iterator(const std::set<PlayerName, PlayerName::sort>::const_reverse_iterator i) noexcept : std::set<PlayerName, PlayerName::sort>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return data_.empty();
  }

  std::size_t size() const noexcept {
    return data_.size();
  }

  iterator begin() const noexcept {
    return iterator(data_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  reverse_iterator rbegin() const noexcept {
    return reverse_iterator(data_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(data_.crbegin());
  }

  iterator end() const noexcept {
    return iterator(data_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(data_.cend());
  }

  reverse_iterator rend() const noexcept {
    return reverse_iterator(data_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(data_.crend());
  }

  bool exists(const PlayerName& player_name) const noexcept {
    return data_.find(player_name) != data_.cend();
  }

  iterator find(const PlayerName& player_name) const noexcept {
    return {data_.find(player_name)};
  }

  /// \brief Insert an additional player.
  std::pair<iterator, bool> insert(const PlayerName& player_name) noexcept {
    return {data_.insert(player_name)};
  }

  bool operator==(const PlayerNames& other) const noexcept {
    return data_ == other.data_;
  }

  bool operator!=(const PlayerNames& other) const noexcept {
    return data_ != other.data_;
  }

  bool operator<(const PlayerNames& other) const noexcept {
    return data_ < other.data_;
  }

  bool operator<=(const PlayerNames& other) const noexcept {
    return data_ <= other.data_;
  }

  bool operator>(const PlayerNames& other) const noexcept {
    return data_ > other.data_;
  }

  bool operator>=(const PlayerNames& other) const noexcept {
    return data_ >= other.data_;
  }

  /// \brief Sort alphabetically.
  struct sort {
    bool operator()(const PlayerNames& player_names_1, const PlayerNames& player_names_2) const noexcept {
      return player_names_1 < player_names_2;
    }
  };

private:

  std::set<PlayerName, PlayerName::sort> data_;

}; // class PlayerNames

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::PlayerNames> {

    size_t operator()(const TI4Echelon::PlayerNames& player_names) const {
      return hash<std::string>()(player_names.print());
    }

  };

} // namespace std
