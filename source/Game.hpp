#pragma once

#include "Date.hpp"
#include "GameMode.hpp"
#include "Standing.hpp"

namespace TI4Echelon {

/// \brief An individual game. Each game consists of a date and a goal number of victory points followed by a list of places, player names, victory points, and faction names.
class Game {

public:

  Game() noexcept {}

  /// \brief Construct a game from a list of lines containing a date and a goal number of victory points followed by a list of places, player names, victory points, and faction names.
  Game(const std::vector<std::string> lines) {
    // 1 header line with a line for each of at least 2 players implies at least 3 lines in total.
    if (lines.size() >= 3) {
      initialize_header(lines[0]);
      for (std::size_t index = 1; index < lines.size(); ++index) {
        initialize_standing(lines[index]);
      }
      check_mode();
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

  GameMode mode() const noexcept {
    return mode_;
  }

  std::optional<std::size_t> number_of_players_on_team(const PlayerName& player_name) const noexcept {
    if (exists(player_name)) {
      switch (mode_) {
        case GameMode::FreeForAll:
          return {1};
          break;
        case GameMode::Teams:
          const std::optional<Place> optional_place{place(player_name)};
          std::size_t counter{0};
          for (const Standing& standing : standings_) {
            if (standing.place() == optional_place.value()) {
              ++counter;
            }
          }
          return {counter};
          break;
      }
    } else {
      const std::optional<std::size_t> no_data;
      return no_data;
    }
  }

  bool exists(const PlayerName& player_name) const noexcept {
    return player_names_.find(player_name) != player_names_.cend();
  }

  bool exists(const FactionName& faction_name) const noexcept {
    return faction_names_.find(faction_name) != faction_names_.cend();
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

  std::set<Place> places(const FactionName& faction) const noexcept {
    std::set<Place> places;
    const std::pair<std::multimap<FactionName, Place, std::less<FactionName>>::const_iterator, std::multimap<FactionName, Place, std::less<FactionName>>::const_iterator> range{faction_names_to_places_.equal_range(faction)};
    for (std::multimap<FactionName, Place, std::less<FactionName>>::const_iterator i = range.first; i != range.second; ++i) {
      places.insert(i->second);
    }
    return places;
  }

  std::set<PlayerName> player_names(const FactionName& faction) const noexcept {
    std::set<PlayerName> player_names;
    const std::pair<std::multimap<FactionName, PlayerName, std::less<FactionName>>::const_iterator, std::multimap<FactionName, PlayerName, std::less<FactionName>>::const_iterator> range{faction_names_to_player_names_.equal_range(faction)};
    for (std::multimap<FactionName, PlayerName, std::less<FactionName>>::const_iterator i = range.first; i != range.second; ++i) {
      player_names.insert(i->second);
    }
    return player_names;
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

  std::set<VictoryPoints> victory_points(const FactionName& faction) const noexcept {
    std::set<VictoryPoints> victory_points;
    const std::pair<std::multimap<FactionName, VictoryPoints, std::less<FactionName>>::const_iterator, std::multimap<FactionName, VictoryPoints, std::less<FactionName>>::const_iterator> range{faction_names_to_victory_points_.equal_range(faction)};
    for (std::multimap<FactionName, VictoryPoints, std::less<FactionName>>::const_iterator i = range.first; i != range.second; ++i) {
      victory_points.insert(i->second);
    }
    return victory_points;
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

  std::string print() const noexcept {
    std::string text{date_.print() + ", " + lowercase(label(mode_)) + ", " + victory_point_goal_.print() + " points, " + std::to_string(size()) + " players, "};
    std::size_t counter{0};
    for (const Standing& standing : standings_) {
      text += standing.print();
      if (counter + 1 < standings_.size()) {
        text += ", ";
      }
      ++counter;
    }
    return text;
  }

  struct iterator : public std::set<Standing, Standing::sort>::iterator {
    iterator(const std::set<Standing, Standing::sort>::iterator i) noexcept : std::set<Standing, Standing::sort>::iterator(i) {}
  };

  struct const_iterator : public std::set<Standing, Standing::sort>::const_iterator {
    const_iterator(const std::set<Standing, Standing::sort>::const_iterator i) noexcept : std::set<Standing, Standing::sort>::const_iterator(i) {}
  };

  struct reverse_iterator : public std::set<Standing, Standing::sort>::reverse_iterator {
    reverse_iterator(const std::set<Standing, Standing::sort>::reverse_iterator i) noexcept : std::set<Standing, Standing::sort>::reverse_iterator(i) {}
  };

  struct const_reverse_iterator : public std::set<Standing, Standing::sort>::const_reverse_iterator {
    const_reverse_iterator(const std::set<Standing, Standing::sort>::const_reverse_iterator i) noexcept : std::set<Standing, Standing::sort>::const_reverse_iterator(i) {}
  };

  bool empty() const noexcept {
    return standings_.empty();
  }

  std::size_t size() const noexcept {
    return standings_.size();
  }

  iterator begin() const noexcept {
   return iterator(standings_.cbegin());
  }

  const_iterator cbegin() const noexcept {
   return const_iterator(standings_.cbegin());
  }

  reverse_iterator rbegin() const noexcept {
   return reverse_iterator(standings_.crbegin());
  }

  const_reverse_iterator crbegin() const noexcept {
   return const_reverse_iterator(standings_.crbegin());
  }

  iterator end() const noexcept {
   return iterator(standings_.cend());
  }

  const_iterator cend() const noexcept {
   return const_iterator(standings_.cend());
  }

  reverse_iterator rend() const noexcept {
   return reverse_iterator(standings_.crend());
  }

  const_reverse_iterator crend() const noexcept {
   return const_reverse_iterator(standings_.crend());
  }

  struct sort {
    bool operator()(const Game& game_1, const Game& game_2) const noexcept {
      return game_1.date() > game_2.date();
    }
  };

private:

  Date date_;

  VictoryPoints victory_point_goal_{10};

  GameMode mode_{GameMode::FreeForAll};

  /// \brief Set of player standings.
  std::set<Standing, Standing::sort> standings_;

  /// \brief Set of player names. Player names are unique.
  std::set<PlayerName, PlayerName::sort_alphabetically> player_names_;

  /// \brief Place of each player name.
  std::map<PlayerName, Place, PlayerName::sort_alphabetically> player_names_to_places_;

  /// \brief Victory points of each player name.
  std::map<PlayerName, VictoryPoints, PlayerName::sort_alphabetically> player_names_to_victory_points_;

  /// \brief Faction name of each player name.
  std::map<PlayerName, FactionName, PlayerName::sort_alphabetically> player_names_to_faction_names_;

  /// \brief Set of faction names. A multiset is used because the Custom faction can appear multiple times.
  std::multiset<FactionName, std::less<FactionName>> faction_names_;

  /// \brief Set of places of each faction name. A multimap is used because the Custom faction can appear multiple times.
  std::multimap<FactionName, Place, std::less<FactionName>> faction_names_to_places_;

  /// \brief Set of player names of each faction name. A multimap is used because the Custom faction can appear multiple times.
  std::multimap<FactionName, PlayerName, std::less<FactionName>> faction_names_to_player_names_;

  /// \brief Set of victory points of each faction name. A multimap is used because the Custom faction can appear multiple times.
  std::multimap<FactionName, VictoryPoints, std::less<FactionName>> faction_names_to_victory_points_;

  void initialize_header(const std::string& line) {
    // The line is expected to read: "<date> <game-mode> <victory-points-goal>""
    const std::vector<std::string> words{split_by_whitespace(line)};
    if (words.size() == 3) {
      date_ = {words[0]};
      const std::optional<GameMode> optional_mode{type<GameMode>(words[1])};
      if (!optional_mode.has_value()) {
        error("'" + words[2] + "' is not a valid game mode for the game played on " + date_.print() + ".");
      }
      mode_ = optional_mode.value();
      victory_point_goal_ = {words[2]};
    } else {
      error("'" + line + "' does not contain a date, a game mode, and a number of victory points.");
    }
  }

  void initialize_standing(const std::string& line) {
    // The line is expected to read: "<place> <player-name> <victory-points> <faction>""
    const std::vector<std::string> words{parse_standing(line)};
    if (words.size() == 4) {
      const Place place{words[0]};
      const PlayerName player_name{words[1]};
      const VictoryPoints victory_points{words[2]};
      const std::optional<FactionName> optional_faction_name{type<FactionName>(words[3])};
      if (!optional_faction_name.has_value()) {
        error("'" + words[3] + "' is not a valid faction for the game played on " + date_.print() + ".");
      }
      standings_.emplace(place, player_name, victory_points, optional_faction_name.value());
      initialize_player_names(place, player_name, victory_points, optional_faction_name.value());
      initialize_faction_names(place, player_name, victory_points, optional_faction_name.value());
    } else {
      error("'" + line + "' does not contain a place, player, number of victory points, and faction for the game played on " + date_.print() + ".");
    }
  }

  std::vector<std::string> parse_standing(const std::string& line) const noexcept {
    // Expect any number of whitespace characters delimiting the place, player name, number of victory points, and faction name.
    // However, expect the words of the faction name to be separated by only a single space.
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
    return words;
  }

  void initialize_player_names(const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) {
    const std::pair<std::set<PlayerName, PlayerName::sort_alphabetically>::const_iterator, bool> result{player_names_.insert(player_name)};
    if (!result.second) {
      error("Player '" + player_name.value() + "' appears twice in the game played on " + date_.print() + ".");
    }
    player_names_to_places_.emplace(player_name, place);
    player_names_to_victory_points_.emplace(player_name, victory_points);
    player_names_to_faction_names_.emplace(player_name, faction_name);
  }

  void initialize_faction_names(const Place& place, const PlayerName& player_name, const VictoryPoints& victory_points, const FactionName& faction_name) noexcept {
    faction_names_.insert(faction_name);
    faction_names_to_places_.emplace(faction_name, place);
    faction_names_to_player_names_.emplace(faction_name, player_name);
    faction_names_to_victory_points_.emplace(faction_name, victory_points);
  }

  void check_mode() noexcept {
    switch (mode_) {
      case GameMode::FreeForAll:
        check_mode_free_for_all();
        break;
      case GameMode::Teams:
        // Nothing to check. By definition, all players on the same team have the same place; this is how teams are identified.
        break;
    }
  }

  /// \brief In free-for-all games, each player must have a unique place.
  void check_mode_free_for_all() const noexcept {
    std::set<Place, Place::sort_ascending> places;
    for (const Standing& standing : standings_) {
      const std::pair<std::set<Place, Place::sort_ascending>::const_iterator, bool> result{places.insert(standing.place())};
      if (!result.second) {
        error("Place '" + standing.place().print() + "' appears twice in the free-for-all game played on " + date_.print() + ".");
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
