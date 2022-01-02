#pragma once

#include "Place.hpp"
#include "PlayerNames.hpp"

namespace TI4Echelon {

/// \brief Team of players in a game.
class Team {

public:

  /// \brief Default constructor. Initializes to an empty team.
  Team() noexcept {}

  /// \brief Constructor that initializes the set to a single player name. Additional player names can be inserted later.
  Team(const Place& place, const PlayerName& player_name) noexcept : place_(place), player_names_(player_name) {}

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
    return place_ == other.place_ && player_names_ == other.player_names_;
  }

  bool operator!=(const Team& other) const noexcept {
    return place_ != other.place_ || player_names_ != other.player_names_;
  }

  bool operator<(const Team& other) const noexcept {
    if (place_ < other.place_) {
      return true;
    } else if (place_ > other.place_) {
      return false;
    } else {
      return player_names_ < other.player_names_;
    }
  }

  bool operator<=(const Team& other) const noexcept {
    if (place_ < other.place_) {
      return true;
    } else if (place_ > other.place_) {
      return false;
    } else {
      return player_names_ <= other.player_names_;
    }
  }

  bool operator>(const Team& other) const noexcept {
    if (place_ < other.place_) {
      return false;
    } else if (place_ > other.place_) {
      return true;
    } else {
      return player_names_ > other.player_names_;
    }
  }

  bool operator>=(const Team& other) const noexcept {
    if (place_ < other.place_) {
      return false;
    } else if (place_ > other.place_) {
      return true;
    } else {
      return player_names_ >= other.player_names_;
    }
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
      return hash<TI4Echelon::Place>()(team.place()) ^ hash<TI4Echelon::PlayerNames>()(team.player_names());
    }

  };

} // namespace std
