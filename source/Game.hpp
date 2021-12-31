#pragma once

#include "Date.hpp"
#include "FactionName.hpp"
#include "Place.hpp"
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
      check_places();
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
    std::string text{date_.print() + " " + victory_point_goal_.print() + " points " + std::to_string(number_of_players()) + " players: "};
    std::size_t counter{0};
    for (const std::pair<Place, PlayerName>& place_and_player_name : places_to_player_names_) {
      player_names_to_victory_points_.find(place_and_player_name.second)->second;
      text += place_and_player_name.first.print() + " " + place_and_player_name.second.value() + " " + player_names_to_victory_points_.find(place_and_player_name.second)->second.print() + " " + label(player_names_to_faction_names_.find(place_and_player_name.second)->second);
      if (counter + 1 < places_to_player_names_.size()) {
        text += ", ";
      }
      ++counter;
    }
    text += ".";
    return text;
  }

  std::size_t number_of_players() const noexcept {
    return player_names_.size();
  }

  bool participant(const PlayerName& player_name) const noexcept {
    return player_names_.find(player_name) != player_names_.cend();
  }

  bool participant(const FactionName& faction) const noexcept {
    return faction_names_.find(faction) != faction_names_.cend();
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

  std::optional<VictoryPoints> victory_points(const PlayerName& player_name) const noexcept {
    const std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically>::const_iterator found{player_names_to_victory_points_.find(player_name)};
    if (found != player_names_to_victory_points_.cend()) {
      return {found->second};
    } else {
      const std::optional<VictoryPoints> no_data;
      return no_data;
    }
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

  std::optional<FactionName> faction_name(const PlayerName& player_name) const noexcept {
    const std::map<PlayerName, FactionName, PlayerName::sort_alphabetically>::const_iterator found{player_names_to_faction_names_.find(player_name)};
    if (found != player_names_to_faction_names_.cend()) {
      return {found->second};
    } else {
      const std::optional<FactionName> no_data;
      return no_data;
    }
  }

  std::optional<PlayerName> player_name(const FactionName& faction_name) const noexcept {
    if (faction_name != FactionName::Custom) {
      const std::multimap<FactionName, PlayerName>::const_iterator found{faction_names_to_player_names_.find(faction_name)};
      if (found != faction_names_to_player_names_.cend()) {
        return {found->second};
      }
    }
    const std::optional<PlayerName> no_data;
    return no_data;
  }

  struct sort_by_most_recent_date {
    bool operator()(const Game& game_1, const Game& game_2) const noexcept {
      return game_1.date() > game_2.date();
    }
  };

private:

  Date date_;

  VictoryPoints victory_point_goal_{10};

  std::set<PlayerName, PlayerName::sort_alphabetically> player_names_;

  std::map<PlayerName, Place, PlayerName::sort_alphabetically> player_names_to_places_;

  std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically> player_names_to_victory_points_;

  std::map<PlayerName, FactionName, PlayerName::sort_alphabetically> player_names_to_faction_names_;

  std::map<Place, PlayerName, Place::sort_ascending> places_to_player_names_;

  std::set<FactionName, std::less<FactionName>> faction_names_;

  /// \brief The Custom faction can appear multiple times, so we use a multimap.
  std::multimap<FactionName, PlayerName> faction_names_to_player_names_;

  /// \brief The Custom faction can appear multiple times, so we use a multimap.
  std::multimap<FactionName, Place, std::less<FactionName>> faction_names_to_places_;

  /// \brief The Custom faction can appear multiple times, so we use a multimap.
  std::multimap<FactionName, VictoryPoints, std::less<FactionName>> faction_names_to_victory_points_;

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
    // The line is expected to read: "<place> <player-name> <victory-points> <faction>""
    std::vector<std::string> words;
    std::string word;
    for (const char c : line) {
      if (::isspace(c) && words.size() < 3) {
        if (!word.empty()) {
          words.push_back(word);
          word.clear();
        }
      } else {
        word.push_back(c);
      }
    }
    words.push_back(word);
    Place place;
    PlayerName player_name;
    VictoryPoints victory_points;
    FactionName faction_name;
    if (words.size() == 4) {
      place = {words[0]};
      player_name = {words[1]};
      victory_points = {words[2]};
      std::string faction_name_string;
      for (std::size_t index = 3; index < words.size(); ++index) {
        if (!faction_name_string.empty()) {
          faction_name_string += " ";
        }
        faction_name_string += words[index];
      }
      const std::optional<FactionName> optional_faction_name{type<FactionName>(faction_name_string)};
      if (optional_faction_name.has_value()) {
        faction_name = optional_faction_name.value();
      } else {
        error("'" + faction_name_string + "' is not a valid faction in the game played on " + date_.print() + ".");
      }
      // Try to insert the player name.
      const std::pair<std::set<PlayerName, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_1{player_names_.insert(player_name)};
      const std::pair<std::map<PlayerName, Place, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_2{player_names_to_places_.emplace(player_name, place)};
      const std::pair<std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_3{player_names_to_victory_points_.emplace(player_name, victory_points)};
      const std::pair<std::map<PlayerName, FactionName, PlayerName::sort_alphabetically>::iterator, bool> player_name_result_4{player_names_to_faction_names_.emplace(player_name, faction_name)};
      if (!player_name_result_1.second || !player_name_result_2.second || !player_name_result_3.second || !player_name_result_4.second) {
        error("Player '" + player_name.value() + "' appears twice in the game played on " + date_.print() + ".");
      }
      // Try to insert the place.
      const std::pair<std::map<Place, PlayerName, std::less<Place>>::iterator, bool> place_result{places_to_player_names_.emplace(place, player_name)};
      if (!place_result.second) {
        error("Place '" + place.print() + "' appears twice in the game played on " + date_.print() + ".");
      }
      // Try to insert the faction.
      const std::pair<std::set<FactionName, std::less<FactionName>>::iterator, bool> faction_result{faction_names_.insert(faction_name)};
      if (!faction_result.second && faction_name != FactionName::Custom) {
        error("FactionName '" + label(faction_name) + "' appears twice in the game played on " + date_.print() + ".");
      }
      faction_names_to_player_names_.emplace(faction_name, player_name);
      faction_names_to_places_.emplace(faction_name, place);
      faction_names_to_victory_points_.emplace(faction_name, victory_points);
    } else {
      error("'" + line + "' does not contain a place, player, number of victory points, and faction in the game played on " + date_.print() + ".");
    }
  }

  void check_places() const {
    // Each game should have each place up to its number of players.
    std::set<Place> expected_places;
    const int8_t limit{static_cast<int8_t>(number_of_players())};
    for (int8_t player_index = 0; player_index < limit; ++player_index) {
      expected_places.emplace(player_index + 1);
    }
    for (const Place& place : expected_places) {
      if (places_to_player_names_.find(place) == places_to_player_names_.cend()) {
        error("The " + place.print() + " place is missing from the game played on " + date_.print() + ".");
      }
    }
  }

}; // class Game

} // namespace TI4Echelon

namespace std {

  template <> struct hash<TI4Echelon::Game> {

    size_t operator()(const TI4Echelon::Game& game) const {
      return hash<TI4Echelon::Date>()(game.date()) ^ hash<TI4Echelon::VictoryPoints>()(game.victory_point_goal());
    }

  };

} // namespace std
