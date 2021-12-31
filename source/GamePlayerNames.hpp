#pragma once

#include "Date.hpp"
#include "FactionName.hpp"
#include "Place.hpp"
#include "PlayerName.hpp"
#include "VictoryPoints.hpp"

namespace TI4Echelon {

/// \brief List of player name attributes in a game.
class GamePlayerNames {

public:

  GamePlayerNames() noexcept {}

  void insert(const Date& date, const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) {
    const std::pair<std::set<PlayerName, PlayerName::sort_alphabetically>::const_iterator, bool> result{player_names_.insert(player_name)};
    if (!result.second) {
      error("Player '" + player_name.value() + "' appears twice in the game played on " + date.print() + ".");
    }
    player_names_to_places_.emplace(player_name, place);
    player_names_to_victory_points_.emplace(player_name, victory_points);
    player_names_to_faction_names_.emplace(player_name, faction_name);
  }

  bool exists(const PlayerName& player_name) const noexcept {
    return player_names_.find(player_name) != player_names_.cend();
  }

  std::optional<Place> place(const PlayerName& player_name) const noexcept {
    const std::map<PlayerName, Place, PlayerName::sort_alphabetically>::const_iterator found{player_names_to_places_.find(player_name)};
    if (found != player_names_to_places_.cend()) {
      return {found->second};
    } else {
      const std::optional<Place> no_data;
      return no_data;
    }
  }

  std::optional<VictoryPoints> victory_points(const PlayerName& player_name) const noexcept {
    const std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically>::const_iterator found{player_names_to_victory_points_.find(player_name)};
    if (found != player_names_to_victory_points_.cend()) {
      return {found->second};
    } else {
      const std::optional<VictoryPoints> no_data;
      return no_data;
    }
  }

  std::optional<FactionName> faction_name(const PlayerName& player_name) const noexcept {
    const std::map<PlayerName, FactionName, PlayerName::sort_alphabetically>::const_iterator found{player_names_to_faction_names_.find(player_name)};
    if (found != player_names_to_faction_names_.cend()) {
      return {found->second};
    } else {
      const std::optional<FactionName> no_data;
      return no_data;
    }
  }

  struct iterator : public std::set<PlayerName, PlayerName::sort_alphabetically>::iterator {
    iterator(const std::set<PlayerName, PlayerName::sort_alphabetically>::iterator i) noexcept : std::set<PlayerName, PlayerName::sort_alphabetically>::iterator(i) {}
  };

  struct const_iterator : public std::set<PlayerName, PlayerName::sort_alphabetically>::const_iterator {
    const_iterator(const std::set<PlayerName, PlayerName::sort_alphabetically>::const_iterator i) noexcept : std::set<PlayerName, PlayerName::sort_alphabetically>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::set<PlayerName, PlayerName::sort_alphabetically>::reverse_iterator {
    reverse_iterator(const std::set<PlayerName, PlayerName::sort_alphabetically>::reverse_iterator i) noexcept : std::set<PlayerName, PlayerName::sort_alphabetically>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::set<PlayerName, PlayerName::sort_alphabetically>::const_reverse_iterator {
    const_reverse_iterator(const std::set<PlayerName, PlayerName::sort_alphabetically>::const_reverse_iterator i) noexcept : std::set<PlayerName, PlayerName::sort_alphabetically>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return player_names_.empty();
  }

  std::size_t size() const noexcept {
    return player_names_.size();
  }

  iterator begin() const noexcept {
   return iterator(player_names_.begin());
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(player_names_.cbegin());
  }

  reverse_iterator rbegin() const noexcept {
   return reverse_iterator(player_names_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
   return const_reverse_iterator(player_names_.crbegin());
  }

  iterator end() const noexcept {
   return iterator(player_names_.end());
  }

  const_iterator cend() const noexcept {
   return const_iterator(player_names_.cend());
  }

  reverse_iterator rend() const noexcept {
   return reverse_iterator(player_names_.rend());
  }

  const_reverse_iterator crend() const noexcept {
   return const_reverse_iterator(player_names_.crend());
  }

private:

  std::set<PlayerName, PlayerName::sort_alphabetically> player_names_;

  std::map<PlayerName, Place, PlayerName::sort_alphabetically> player_names_to_places_;

  std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically> player_names_to_victory_points_;

  std::map<PlayerName, FactionName, PlayerName::sort_alphabetically> player_names_to_faction_names_;

}; // class GamePlayerNames

} // namespace TI4Echelon
