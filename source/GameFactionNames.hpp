#pragma once

#include "Date.hpp"
#include "FactionName.hpp"
#include "Place.hpp"
#include "PlayerName.hpp"
#include "VictoryPoints.hpp"

namespace TI4Echelon {

/// \brief List of faction name attributes in a game.
class GameFactionNames {

public:

  GameFactionNames() noexcept {}

  void insert(const Date& date, const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) {
    const std::pair<std::set<FactionName, std::less<FactionName>>::const_iterator, bool> faction_result{faction_names_.insert(faction_name)};
    if (!faction_result.second && faction_name != FactionName::Custom) {
      error("The '" + label(faction_name) + "' faction appears twice in the game played on " + date.print() + ".");
    }
    if (faction_name != FactionName::Custom) {
      faction_names_to_places_.emplace(faction_name, place);
      faction_names_to_player_names_.emplace(faction_name, player_name);
      faction_names_to_victory_points_.emplace(faction_name, victory_points);
    }
  }

  bool exists(const FactionName& faction_name) const noexcept {
    return faction_names_.find(faction_name) != faction_names_.cend();
  }

  std::optional<Place> place(const FactionName& faction) const noexcept {
    if (faction != FactionName::Custom) {
      const std::map<FactionName, Place, std::less<FactionName>>::const_iterator found{faction_names_to_places_.find(faction)};
      if (found != faction_names_to_places_.cend()) {
        return {found->second};
      }
    }
    const std::optional<Place> no_data;
    return no_data;
  }

  std::optional<VictoryPoints> victory_points(const FactionName& faction) const noexcept {
    if (faction != FactionName::Custom) {
      const std::map<FactionName, VictoryPoints, std::less<FactionName>>::const_iterator found{faction_names_to_victory_points_.find(faction)};
      if (found != faction_names_to_victory_points_.cend()) {
        return {found->second};
      }
    }
    const std::optional<VictoryPoints> no_data;
    return no_data;
  }

  std::optional<PlayerName> player_name(const FactionName& faction_name) const noexcept {
    if (faction_name != FactionName::Custom) {
      const std::map<FactionName, PlayerName>::const_iterator found{faction_names_to_player_names_.find(faction_name)};
      if (found != faction_names_to_player_names_.cend()) {
        return {found->second};
      }
    }
    const std::optional<PlayerName> no_data;
    return no_data;
  }

  struct iterator : public std::set<FactionName, std::less<FactionName>>::iterator {
    iterator(const std::set<FactionName, std::less<FactionName>>::iterator i) noexcept : std::set<FactionName, std::less<FactionName>>::iterator(i) {}
  };

  struct const_iterator : public std::set<FactionName, std::less<FactionName>>::const_iterator {
    const_iterator(const std::set<FactionName, std::less<FactionName>>::const_iterator i) noexcept : std::set<FactionName, std::less<FactionName>>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::set<FactionName, std::less<FactionName>>::reverse_iterator {
    reverse_iterator(const std::set<FactionName, std::less<FactionName>>::reverse_iterator i) noexcept : std::set<FactionName, std::less<FactionName>>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::set<FactionName, std::less<FactionName>>::const_reverse_iterator {
    const_reverse_iterator(const std::set<FactionName, std::less<FactionName>>::const_reverse_iterator i) noexcept : std::set<FactionName, std::less<FactionName>>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return faction_names_.empty();
  }

  std::size_t size() const noexcept {
    return faction_names_.size();
  }

  iterator begin() const noexcept {
   return iterator(faction_names_.begin());
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(faction_names_.cbegin());
  }

  reverse_iterator rbegin() const noexcept {
   return reverse_iterator(faction_names_.rbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
   return const_reverse_iterator(faction_names_.crbegin());
  }

  iterator end() const noexcept {
   return iterator(faction_names_.end());
  }

  const_iterator cend() const noexcept {
   return const_iterator(faction_names_.cend());
  }

  reverse_iterator rend() const noexcept {
   return reverse_iterator(faction_names_.rend());
  }

  const_reverse_iterator crend() const noexcept {
   return const_reverse_iterator(faction_names_.crend());
  }

private:

  std::set<FactionName, std::less<FactionName>> faction_names_;

  std::map<FactionName, Place, std::less<FactionName>> faction_names_to_places_;

  std::map<FactionName, PlayerName, std::less<FactionName>> faction_names_to_player_names_;

  std::map<FactionName, VictoryPoints, std::less<FactionName>> faction_names_to_victory_points_;

}; // class GameFactionNames

} // namespace TI4Echelon
