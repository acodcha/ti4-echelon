#pragma once

#include "Date.hpp"
#include "FactionName.hpp"
#include "Place.hpp"
#include "PlayerName.hpp"
#include "VictoryPoints.hpp"

namespace TI4Echelon {

/// \brief List of place attributes in a game.
class GamePlaces {

public:

  GamePlaces() noexcept {}

  void insert(const Date& date, const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) {
    const std::pair<std::set<Place, Place::sort_ascending>::const_iterator, bool> result{places_.insert(place)};
    if (!result.second) {
      error("Place '" + place.print() + "' appears twice in the game played on " + date.print() + ".");
    }
    places_to_player_names_.emplace(place, player_name);
    places_to_victory_points_.emplace(place, victory_points);
    places_to_faction_names_.emplace(place, faction_name);
  }

  bool exists(const Place& place) const noexcept {
    return places_.find(place) != places_.cend();
  }

  std::optional<PlayerName> player_name(const Place& place) const noexcept {
    const std::map<Place, PlayerName, Place::sort_ascending>::const_iterator found{places_to_player_names_.find(place)};
    if (found != places_to_player_names_.cend()) {
      return {found->second};
    } else {
      const std::optional<PlayerName> no_data;
      return no_data;
    }
  }

  std::optional<VictoryPoints> victory_points(const Place& place) const noexcept {
    const std::map<Place, VictoryPoints, Place::sort_ascending>::const_iterator found{places_to_victory_points_.find(place)};
    if (found != places_to_victory_points_.cend()) {
      return {found->second};
    } else {
      const std::optional<VictoryPoints> no_data;
      return no_data;
    }
  }

  std::optional<FactionName> faction_name(const Place& place) const noexcept {
    const std::map<Place, FactionName, Place::sort_ascending>::const_iterator found{places_to_faction_names_.find(place)};
    if (found != places_to_faction_names_.cend()) {
      return {found->second};
    } else {
      const std::optional<FactionName> no_data;
      return no_data;
    }
  }

  struct iterator : public std::set<Place, Place::sort_ascending>::iterator {
    iterator(const std::set<Place, Place::sort_ascending>::iterator i) noexcept : std::set<Place, Place::sort_ascending>::iterator(i) {}
  };

  struct const_iterator : public std::set<Place, Place::sort_ascending>::const_iterator {
    const_iterator(const std::set<Place, Place::sort_ascending>::const_iterator i) noexcept : std::set<Place, Place::sort_ascending>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::set<Place, Place::sort_ascending>::reverse_iterator {
    reverse_iterator(const std::set<Place, Place::sort_ascending>::reverse_iterator i) noexcept : std::set<Place, Place::sort_ascending>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::set<Place, Place::sort_ascending>::const_reverse_iterator {
    const_reverse_iterator(const std::set<Place, Place::sort_ascending>::const_reverse_iterator i) noexcept : std::set<Place, Place::sort_ascending>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return places_.empty();
  }

  std::size_t size() const noexcept {
    return places_.size();
  }

  iterator begin() const noexcept {
   return iterator(places_.begin());
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(places_.cbegin());
  }

  reverse_iterator rbegin() const noexcept {
   return reverse_iterator(places_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
   return const_reverse_iterator(places_.crbegin());
  }

  iterator end() const noexcept {
   return iterator(places_.end());
  }

  const_iterator cend() const noexcept {
   return const_iterator(places_.cend());
  }

  reverse_iterator rend() const noexcept {
   return reverse_iterator(places_.rend());
  }

  const_reverse_iterator crend() const noexcept {
   return const_reverse_iterator(places_.crend());
  }

private:

  std::set<Place, Place::sort_ascending> places_;

  std::map<Place, PlayerName, Place::sort_ascending> places_to_player_names_;

  std::map<Place, VictoryPoints, Place::sort_ascending> places_to_victory_points_;

  std::map<Place, FactionName, Place::sort_ascending> places_to_faction_names_;

}; // class GamePlaces

} // namespace TI4Echelon
