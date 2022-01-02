#pragma once

#include "Team.hpp"

namespace TI4Echelon {

/// \brief Set of teams in a game.
class Teams {

public:

  /// \brief Default constructor. Initializes an empty set of teams.
  Teams() noexcept {}

  struct const_iterator : public std::set<Team, Team::sort>::const_iterator {
    const_iterator(const std::set<Team, Team::sort>::const_iterator i) noexcept : std::set<Team, Team::sort>::const_iterator(i) {}
  };

  struct const_reverse_iterator : public std::set<Team, Team::sort>::const_reverse_iterator {
    const_reverse_iterator(const std::set<Team, Team::sort>::const_reverse_iterator i) noexcept : std::set<Team, Team::sort>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return data_.empty();
  }

  std::size_t size() const noexcept {
    return data_.size();
  }

  const_iterator begin() const noexcept {
    return const_iterator(data_.begin());
  }

  const_iterator cbegin() const noexcept {
    return const_iterator(data_.cbegin());
  }

  const_reverse_iterator rbegin() const noexcept {
    return const_reverse_iterator(data_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
    return const_reverse_iterator(data_.crbegin());
  }

  const_iterator end() const noexcept {
    return const_iterator(data_.end());
  }

  const_iterator cend() const noexcept {
    return const_iterator(data_.cend());
  }

  const_reverse_iterator rend() const noexcept {
    return const_reverse_iterator(data_.rend());
  }

  const_reverse_iterator crend() const noexcept {
    return const_reverse_iterator(data_.crend());
  }

  const_iterator find(const Place& place) const noexcept {
    return {data_.find({place})};
  }

  std::pair<const_iterator, bool> emplace(const Place& place, const PlayerName& player_name) noexcept {
    return {data_.emplace(place, player_name)};
  }

  std::pair<const_iterator, bool> emplace(const Place& place, const PlayerNames& player_names) noexcept {
    return {data_.emplace(place, player_names)};
  }

  std::pair<const_iterator, bool> insert(const Team& team) noexcept {
    return {data_.insert(team)};
  }

  const_iterator erase(const const_iterator& i) noexcept {
    return {data_.erase(i)};
  }

private:

  std::set<Team, Team::sort> data_;

}; // class Teams

} // namespace TI4Echelon
