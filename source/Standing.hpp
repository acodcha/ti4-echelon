#pragma once

#include "Factions.hpp"
#include "Place.hpp"
#include "PlayerName.hpp"
#include "VictoryPoints.hpp"

namespace TI4Echelon {

/// \brief Standing of a player within a game, including place, player name, number of victory points, and faction.
class Standing {

public:

  Standing() noexcept {}

  Standing(const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const Faction& faction) noexcept : place_(place), player_name_(player_name), victory_points_(victory_points), faction_(faction) {}

  constexpr const Place& place() const noexcept {
    return place_;
  }

  const PlayerName& player_name() const noexcept {
    return player_name_;
  }

  constexpr const VictoryPoints& victory_points() const noexcept {
    return victory_points_;
  }

  constexpr const Faction& faction() const noexcept {
    return faction_;
  }

  std::string print() const noexcept {
    return place_.print() + " " + player_name_.value() + " " + victory_points_.print() + " " + label(faction_);
  }

  constexpr bool operator==(const Standing& other) const noexcept {
    return place_ == other.place_;
  }

  constexpr bool operator!=(const Standing& other) const noexcept {
    return place_ != other.place_;
  }

  constexpr bool operator<(const Standing& other) const noexcept {
    return place_ < other.place_;
  }

  constexpr bool operator<=(const Standing& other) const noexcept {
    return place_ <= other.place_;
  }

  constexpr bool operator>(const Standing& other) const noexcept {
    return place_ > other.place_;
  }

  constexpr bool operator>=(const Standing& other) const noexcept {
    return place_ >= other.place_;
  }

  struct sort_by_ascending_place {
    bool operator()(const Standing& standing_1, const Standing& standing_2) const noexcept {
      return standing_1.place() < standing_2.place();
    }
  };

private:

  Place place_;

  PlayerName player_name_;

  VictoryPoints victory_points_;

  Faction faction_{Faction::Custom};

}; // class Standing

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Standing> {

    size_t operator()(const TI4Echelon::Standing& standing) const {
      return hash<TI4Echelon::Place>()(standing.place()) ^ hash<TI4Echelon::PlayerName>()(standing.player_name()) ^ hash<TI4Echelon::VictoryPoints>()(standing.victory_points()) ^ hash<TI4Echelon::Faction>()(standing.faction());
    }

  };

} // namespace std
