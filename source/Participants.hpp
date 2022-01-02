#pragma once

#include "Participant.hpp"

namespace TI4Echelon {

/// \brief Set of participants in a game.
class Participants {

public:

  /// \brief Default constructor. Initializes an empty set of participants.
  Participants() noexcept {}

  struct const_iterator : public std::set<Participant, Participant::sort>::const_iterator {
    const_iterator(const std::set<Participant, Participant::sort>::const_iterator i) noexcept : std::set<Participant, Participant::sort>::const_iterator(i) {}
  };

  struct const_reverse_iterator : public std::set<Participant, Participant::sort>::const_reverse_iterator {
    const_reverse_iterator(const std::set<Participant, Participant::sort>::const_reverse_iterator i) noexcept : std::set<Participant, Participant::sort>::const_reverse_iterator(i) {}
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

  std::pair<const_iterator, bool> insert(const Participant& participant) noexcept {
    return {data_.insert(participant)};
  }

  std::pair<const_iterator, bool> emplace(const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) noexcept {
    return {data_.emplace(place, player_name, victory_points, faction_name)};
  }

private:

  std::set<Participant, Participant::sort> data_;

}; // class Participants

} // namespace TI4Echelon
