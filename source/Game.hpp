#pragma once

#include "Date.hpp"
#include "Factions.hpp"
#include "Places.hpp"
#include "PlayerName.hpp"
#include "VictoryPoints.hpp"

namespace TI4Echelon {

/// \brief An individual game. Each game consists of a date and a goal number of victory points followed by a list of places, player names, victory points, and faction names.
class Game {

public:

  Game() noexcept {}

  /// \brief Construct a game from a list of lines containing a date and a goal number of victory points followed by a list of places, player names, victory points, and faction names.
  Game(const std::vector<std::string> lines) {
    if (lines.size() >= 2) {
      initialize_date_and_victory_point_goal(lines[0]);
      for (std::size_t index = 1; index < lines.size(); ++index) {
        initialize_standing(lines[index]);
      }
    } else {
      error("Cannot parse the lines of text for a game.");
    }
  }

  constexpr const Date& date() const noexcept {
    return date_;
  }

  constexpr const VictoryPoints& victory_point_goal() const noexcept {
    return victory_point_goal_;
  }

  std::string print() const noexcept {
    std::string text{date_.print() + " " + victory_point_goal_.print() + ": "};
    std::size_t counter{0};
    for (const std::pair<Place, PlayerName>& place_and_player_name : places_to_player_names_) {
      player_names_to_victory_points_.find(place_and_player_name.second)->second;
      text += label(place_and_player_name.first) + " " + place_and_player_name.second.value() + " " + player_names_to_victory_points_.find(place_and_player_name.second)->second.print() + " " + label(player_names_to_factions_.find(place_and_player_name.second)->second);
      if (counter + 1 < places_to_player_names_.size()) {
        text += ", ";
      }
      ++counter;
    }
    return text;
  }

  bool participant(const PlayerName& player_name) const noexcept {
    return player_names_.find(player_name) != player_names_.cend();
  }

  bool participant(const Faction& faction) const noexcept {
    return factions_.find(faction) != factions_.cend();
  }

private:

  Date date_;

  VictoryPoints victory_point_goal_{10};

  std::set<PlayerName, PlayerName::sort_alphabetically> player_names_;

  std::map<PlayerName, Place, PlayerName::sort_alphabetically> player_names_to_places_;

  std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically> player_names_to_victory_points_;

  std::map<PlayerName, Faction, PlayerName::sort_alphabetically> player_names_to_factions_;

  std::map<Place, PlayerName, std::less<Place>> places_to_player_names_;

  std::set<Faction, std::less<Faction>> factions_;

  /// \brief The Custom faction can appear multiple times, so we use a multimap.
  std::multimap<Faction, PlayerName> factions_to_player_names_;

  void initialize_date_and_victory_point_goal(const std::string& line) {
    const std::vector<std::string> words{split_by_whitespace(line)};
    if (words.size() == 2) {
      date_ = {words[0]};
      victory_point_goal_ = {words[1]};
    } else {
      error("'" + line + "' does not contain a date and a number of victory points.");
    }
  }

  void initialize_standing(const std::string& line) {
    Place place;
    PlayerName player_name;
    VictoryPoints victory_points;
    Faction faction;
    const std::vector<std::string> words{split_by_whitespace(line)};
    if (words.size() >= 4) {
      const std::optional<Place> optional_place{type<Place>(words[0])};
      if (optional_place.has_value()) {
        place = optional_place.value();
      } else {
        error("'" + words[0] + "' is not a valid place.");
      }
      player_name = words[1];
      victory_points = {words[2]};
      std::string faction_name;
      for (std::size_t index = 3; index < words.size(); ++index) {
        faction_name += words[index];
      }
      const std::optional<Faction> optional_faction{type<Faction>(faction_name)};
      if (optional_faction.has_value()) {
        faction = optional_faction.value();
      } else {
        error("'" + faction_name + "' is not a valid faction.");
      }
      // Try to insert the player name.
      const std::pair<std::set<PlayerName, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_1{player_names_.insert(player_name)};
      const std::pair<std::map<PlayerName, Place, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_2{player_names_to_places_.emplace(player_name, place)};
      const std::pair<std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_3{player_names_to_victory_points_.emplace(player_name, victory_points)};
      const std::pair<std::map<PlayerName, Faction, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_4{player_names_to_factions_.emplace(player_name, faction)};
      if (!player_name_result_1.second || !player_name_result_2.second || !player_name_result_3.second || !player_name_result_4.second) {
        error("Player '" + player_name.value() + "' appears twice in the same game.");
      }
      // Try to insert the place.
      const std::pair<std::map<Place, PlayerName, std::less<Place>>::iterator, bool> result3{places_to_player_names_.emplace(place, player_name)};
      if (!result3.second) {
        error("Place '" + label(place) + "' appears twice in the same game.");
      }
      // Insert the faction.
      factions_.insert(faction);
      factions_to_player_names_.emplace(faction, player_name);
    } else {
      error("'" + line + "' does not contain a place, player name, number of victory points, and faction.");
    }
  }

}; // class Game

} // namespace TI4Echelon
