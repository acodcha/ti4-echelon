#pragma once

#include "FactionName.hpp"
#include "Place.hpp"
#include "PlayerName.hpp"
#include "VictoryPoints.hpp"

namespace TI4Echelon {

/// \brief Standing of a participant in a game. Includes a place, a player name, a number of victory points, and a faction name.
class Participant {

public:

  Participant() noexcept {}

  Participant(const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) noexcept :
    place_(place), player_name_(player_name), victory_points_(victory_points), faction_name_(faction_name) {}

  constexpr const Place& place() const noexcept {
    return place_;
  }

  const PlayerName& player_name() const noexcept {
    return player_name_;
  }

  constexpr const VictoryPoints& victory_points() const noexcept {
    return victory_points_;
  }

  constexpr const FactionName& faction_name() const noexcept {
    return faction_name_;
  }

  std::string print() const noexcept {
    return place_.print() + " " + player_name_.value() + " " + victory_points_.print() + " " + label(faction_name_);
  }

  bool operator==(const Participant& other) const noexcept {
    return place_ == other.place_ && player_name_ == other.player_name_ && victory_points_ == other.victory_points_ && faction_name_ == other.faction_name_;
  }

  bool operator!=(const Participant& other) const noexcept {
    return place_ != other.place_ || player_name_ != other.player_name_ || victory_points_ != other.victory_points_ || faction_name_ != other.faction_name_;
  }

  bool operator<(const Participant& other) const noexcept {
    if (place_ < other.place_) {
      return true;
    } else if (place_ > other.place_) {
      return false;
    } else {
      if (victory_points_ > other.victory_points_) {
        return true;
      } else if (victory_points_ < other.victory_points_) {
        return false;
      } else {
        if (player_name_ < other.player_name_) {
          return true;
        } else if (player_name_ > other.player_name_) {
          return false;
        } else {
          return faction_name_ < other.faction_name_;
        }
      }
    }
  }

  bool operator<=(const Participant& other) const noexcept {
    if (place_ < other.place_) {
      return true;
    } else if (place_ > other.place_) {
      return false;
    } else {
      if (victory_points_ > other.victory_points_) {
        return true;
      } else if (victory_points_ < other.victory_points_) {
        return false;
      } else {
        if (player_name_ < other.player_name_) {
          return true;
        } else if (player_name_ > other.player_name_) {
          return false;
        } else {
          return faction_name_ <= other.faction_name_;
        }
      }
    }
  }

  bool operator>(const Participant& other) const noexcept {
    if (place_ < other.place_) {
      return false;
    } else if (place_ > other.place_) {
      return true;
    } else {
      if (victory_points_ > other.victory_points_) {
        return false;
      } else if (victory_points_ < other.victory_points_) {
        return true;
      } else {
        if (player_name_ < other.player_name_) {
          return false;
        } else if (player_name_ > other.player_name_) {
          return true;
        } else {
          return faction_name_ > other.faction_name_;
        }
      }
    }
  }

  bool operator>=(const Participant& other) const noexcept {
    if (place_ < other.place_) {
      return false;
    } else if (place_ > other.place_) {
      return true;
    } else {
      if (victory_points_ > other.victory_points_) {
        return false;
      } else if (victory_points_ < other.victory_points_) {
        return true;
      } else {
        if (player_name_ < other.player_name_) {
          return false;
        } else if (player_name_ > other.player_name_) {
          return true;
        } else {
          return faction_name_ >= other.faction_name_;
        }
      }
    }
  }

  /// \brief Sort by best participant to worst participant.
  struct sort {
    bool operator()(const Participant& participant_1, const Participant& participant_2) const noexcept {
      return participant_1 < participant_2;
    }
  };

private:

  Place place_;

  PlayerName player_name_;

  VictoryPoints victory_points_;

  FactionName faction_name_{FactionName::Custom};

}; // class Participant

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Participant> {

    size_t operator()(const TI4Echelon::Participant& participant) const {
      return hash<TI4Echelon::Place>()(participant.place()) ^ hash<TI4Echelon::PlayerName>()(participant.player_name()) ^ hash<TI4Echelon::VictoryPoints>()(participant.victory_points()) ^ hash<TI4Echelon::FactionName>()(participant.faction_name());
    }

  };

} // namespace std
