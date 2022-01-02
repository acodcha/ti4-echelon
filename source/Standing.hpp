#pragma once

#include "FactionName.hpp"
#include "Place.hpp"
#include "PlayerName.hpp"
#include "VictoryPoints.hpp"

namespace TI4Echelon {

/// \brief Standing of a player within a game. Includes a place, a player name, a number of victory points, and a faction name.
class Standing {

public:

  Standing() noexcept {}

  Standing(const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) noexcept :
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

  bool operator==(const Standing& other) const noexcept {
    return place_ == other.place_ && player_name_ == other.player_name_ && victory_points_ == other.victory_points_ && faction_name_ == other.faction_name_;
  }

  bool operator!=(const Standing& other) const noexcept {
    return place_ != other.place_ || player_name_ != other.player_name_ || victory_points_ != other.victory_points_ || faction_name_ != other.faction_name_;
  }

  bool operator<(const Standing& other) const noexcept {
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

  bool operator<=(const Standing& other) const noexcept {
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

  bool operator>(const Standing& other) const noexcept {
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

  bool operator>=(const Standing& other) const noexcept {
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

  struct sort {
    bool operator()(const Standing& standing_1, const Standing& standing_2) const noexcept {
      return standing_1 < standing_2;
    }
  };

private:

  Place place_;

  PlayerName player_name_;

  VictoryPoints victory_points_;

  FactionName faction_name_{FactionName::Custom};

}; // class Standing

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Standing> {

    size_t operator()(const TI4Echelon::Standing& standing) const {
      return hash<TI4Echelon::Place>()(standing.place()) ^ hash<TI4Echelon::PlayerName>()(standing.player_name()) ^ hash<TI4Echelon::VictoryPoints>()(standing.victory_points()) ^ hash<TI4Echelon::FactionName>()(standing.faction_name());
    }

  };

} // namespace std
