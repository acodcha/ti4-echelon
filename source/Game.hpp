#pragma once

#include "GameFactionNames.hpp"
#include "GamePlaces.hpp"
#include "GamePlayerNames.hpp"

namespace TI4Echelon {

/// \brief An individual game. Each game consists of a date and a goal number of victory points followed by a list of places, player names, victory points, and faction names.
class Game {

public:

  Game() noexcept {}

  /// \brief Construct a game from a list of lines containing a date and a goal number of victory points followed by a list of places, player names, victory points, and faction names.
  Game(const std::vector<std::string> lines) {
    // 1 header line with a line for each of at least 2 players implies at least 3 lines in total.
    if (lines.size() >= 3) {
      initialize_date_and_victory_point_goal(lines[0]);
      for (std::size_t index = 1; index < lines.size(); ++index) {
        initialize_standing(lines[index]);
      }
      check_places();
    } else {
      std::string text;
      for (const std::string& line : lines) {
        if (!text.empty()) {
          text += ";";
        }
        text += line;
      }
      error("The lines '" + text + "' cannot be parsed as a game.");
    }
  }

  constexpr const Date& date() const noexcept {
    return date_;
  }

  constexpr const VictoryPoints& victory_point_goal() const noexcept {
    return victory_point_goal_;
  }

  const GameFactionNames& faction_names() const noexcept {
    return faction_names_;
  }

  const GamePlaces& places() const noexcept {
    return places_;
  }

  const GamePlayerNames& player_names() const noexcept {
    return player_names_;
  }

  std::size_t number_of_players() const noexcept {
    return player_names_.size();
  }

  std::string print() const noexcept {
    std::string text{date_.print() + " " + victory_point_goal_.print() + " points " + std::to_string(number_of_players()) + " players: "};
    std::size_t counter{0};
    for (const Place& place : places_) {
      text += place.print() + " " + places_.player_name(place).value().value() + " " + places_.victory_points(place).value().print() + " " + label(places_.faction_name(place).value()) ;
      if (counter + 1 < places_.size()) {
        text += ", ";
      }
      ++counter;
    }
    text += ".";
    return text;
  }

  struct sort_by_most_recent_date {
    bool operator()(const Game& game_1, const Game& game_2) const noexcept {
      return game_1.date() > game_2.date();
    }
  };

private:

  Date date_;

  VictoryPoints victory_point_goal_{10};

  GameFactionNames faction_names_;

  GamePlaces places_;

  GamePlayerNames player_names_;

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
        error("'" + faction_name_string + "' is not a valid faction for the game played on " + date_.print() + ".");
      }
      // Try to insert the attributes.
      faction_names_.insert(date_, place, player_name, victory_points, faction_name);
      places_.insert(date_, place, player_name, victory_points, faction_name);
      player_names_.insert(date_, place, player_name, victory_points, faction_name);
    } else {
      error("'" + line + "' does not contain a place, player, number of victory points, and faction for the game played on " + date_.print() + ".");
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
      if (!places_.exists(place)) {
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
