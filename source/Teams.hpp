#pragma once

#include "Team.hpp"

namespace TI4Echelon {

/// \brief Set of teams in a game. A team consists of a place and a set of player names.
class Teams {

public:

  /// \brief Default constructor. Initializes an empty set of teams.
  Teams() noexcept {}

  struct iterator : public std::map<Place, PlayerNames, Place::sort>::iterator {
    iterator(const std::map<Place, PlayerNames, Place::sort>::iterator i) noexcept : std::map<Place, PlayerNames, Place::sort>::iterator(i) {}
  };

  struct const_iterator : public std::map<Place, PlayerNames, Place::sort>::const_iterator {
    const_iterator(const std::map<Place, PlayerNames, Place::sort>::const_iterator i) noexcept : std::map<Place, PlayerNames, Place::sort>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::map<Place, PlayerNames, Place::sort>::reverse_iterator {
    reverse_iterator(const std::map<Place, PlayerNames, Place::sort>::reverse_iterator i) noexcept : std::map<Place, PlayerNames, Place::sort>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::map<Place, PlayerNames, Place::sort>::const_reverse_iterator {
    const_reverse_iterator(const std::map<Place, PlayerNames, Place::sort>::const_reverse_iterator i) noexcept : std::map<Place, PlayerNames, Place::sort>::const_reverse_iterator(i) {}
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

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  reverse_iterator rbegin() noexcept {
    return reverse_iterator(data_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(data_.crbegin());
  }

  iterator end() noexcept {
    return iterator(data_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(data_.cend());
  }

  reverse_iterator rend() noexcept {
    return reverse_iterator(data_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(data_.crend());
  }

  iterator find(const Place& place) noexcept {
    return {data_.find(place)};
  }

  std::pair<iterator, bool> emplace(const Place& place, const PlayerName& player_name) noexcept {
    return {data_.emplace(place, player_name)};
  }

private:

  std::map<Place, PlayerNames, Place::sort> data_;

}; // class Teams

} // namespace TI4Echelon
