#pragma once

#include "Place.hpp"
#include "PlayerNames.hpp"

namespace TI4Echelon {

/// \brief Team of players in a game.
class Team {

public:

  /// \brief Default constructor. Initializes to an empty team.
  Team() noexcept {}

  /// \brief Constructor that initializes the team to a place without any player names. Player names can be inserted later.
  Team(const Place& place) noexcept : place_(place) {}

  /// \brief Constructor that initializes the team to a place and a single player name. Additional player names can be inserted later.
  Team(const Place& place, const PlayerName& player_name) noexcept : place_(place), player_names_(player_name) {}

  /// \brief Constructor that initializes the team to a place and player names.
  Team(const Place& place, const PlayerNames& player_names) noexcept : place_(place), player_names_(player_names) {}

  const Place& place() const noexcept {
    return place_;
  }

  const PlayerNames& player_names() const noexcept {
    return player_names_;
  }

  PlayerNames& mutable_player_names() noexcept {
    return player_names_;
  }

  std::string print() const noexcept {
    return place_.print() + " " + player_names_.print();
  }

  bool operator==(const Team& other) const noexcept {
    return place_ == other.place_;
  }

  bool operator!=(const Team& other) const noexcept {
    return place_ != other.place_;
  }

  bool operator<(const Team& other) const noexcept {
    return place_ < other.place_;
  }

  bool operator<=(const Team& other) const noexcept {
    return place_ <= other.place_;
  }

  bool operator>(const Team& other) const noexcept {
    return place_ > other.place_;
  }

  bool operator>=(const Team& other) const noexcept {
    return place_ >= other.place_;
  }

  /// \brief Sort from best team to worst team.
  struct sort {
    bool operator()(const Team& team_1, const Team& team_2) const noexcept {
      return team_1 < team_2;
    }
  };

private:

  Place place_;

  PlayerNames player_names_;

}; // class Team

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Team> {

    size_t operator()(const TI4Echelon::Team& team) const {
      return hash<TI4Echelon::Place>()(team.place());
    }

  };

} // namespace std
