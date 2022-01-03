#pragma once

#include "PlayerSnapshot.hpp"

namespace TI4Echelon {

/// \brief A player along with a history of snapshots.
class PlayerSnapshots {

public:

  /// \brief Default constructor. Initializes an empty set of snapshots.
  PlayerSnapshots() noexcept {}

  struct iterator : public std::vector<PlayerSnapshot>::iterator {
    iterator(const std::vector<PlayerSnapshot>::iterator i) noexcept : std::vector<PlayerSnapshot>::iterator(i) {}
  };

  struct const_iterator : public std::vector<PlayerSnapshot>::const_iterator {
    const_iterator(const std::vector<PlayerSnapshot>::const_iterator i) noexcept : std::vector<PlayerSnapshot>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::vector<PlayerSnapshot>::reverse_iterator {
    reverse_iterator(const std::vector<PlayerSnapshot>::reverse_iterator i) noexcept : std::vector<PlayerSnapshot>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::vector<PlayerSnapshot>::const_reverse_iterator {
    const_reverse_iterator(const std::vector<PlayerSnapshot>::const_reverse_iterator i) noexcept : std::vector<PlayerSnapshot>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return data_.empty();
  }

  std::size_t size() const noexcept {
    return data_.size();
  }

  iterator begin() noexcept {
    return iterator(data_.begin());
  }

  const_iterator begin() const noexcept {
    return const_iterator(data_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(data_.rbegin());
  }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(data_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(data_.crbegin());
  }

  iterator end() noexcept {
    return iterator(data_.end());
  }

  const_iterator end() const noexcept {
    return const_iterator(data_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(data_.cend());
  }

  reverse_iterator rend() noexcept {
    return reverse_iterator(data_.rend());
  }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(data_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(data_.crend());
  }

  void emplace_back(
    const PlayerName& name,
    const Game& game,
    const std::unordered_map<PlayerName, EloRating>& elo_ratings
  ) noexcept {
    data_.emplace_back(name, game, elo_ratings, latest());
  }

  std::optional<PlayerSnapshot> latest() const {
    if (!data_.empty()) {
      return {data_.back()};
    } else {
      const std::optional<PlayerSnapshot> no_data;
      return no_data;
    }
  }

private:

  std::vector<PlayerSnapshot> data_;

}; // class PlayerSnapshots

} // namespace TI4Echelon
