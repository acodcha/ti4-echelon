#pragma once

#include "Place.hpp"
#include "PlayerName.hpp"

namespace TI4Echelon {

/// \brief Team of players in a game.
class Team {

public:

  /// \brief Default constructor. Initializes to an empty team.
  Team() noexcept {}

  /// \brief Constructor that initializes the team to a place without any player names. Player names can be inserted later.
  Team(const Place& place) noexcept : place_(place) {}

  /// \brief Constructor that initializes the team to a place and a single player name. Additional player names can be inserted later.
  Team(const Place& place, const PlayerName& player_name) noexcept : place_(place), player_names_({player_name}) {}

  const Place& place() const noexcept {
    return place_;
  }

  bool exists(const PlayerName& player_name) const noexcept {
    return player_names_.find(player_name) != player_names_.cend();
  }

  std::size_t size() const noexcept {
    return player_names_.size();
  }

  std::pair<std::set<PlayerName, PlayerName::sort>::const_iterator, bool> insert(const PlayerName& player_name) noexcept {
    return {player_names_.insert(player_name)};
  }

  std::string print() const noexcept {
    std::string text{place_.print()};
    for (const PlayerName& player_name : player_names_) {
      text += " " + player_name.value();
    }
    return text;
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

  std::set<PlayerName, PlayerName::sort> player_names_;

}; // class Team

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Team> {

    size_t operator()(const TI4Echelon::Team& team) const {
      return hash<TI4Echelon::Place>()(team.place());
    }

  };

} // namespace std
